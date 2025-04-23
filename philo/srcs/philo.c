/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 21:56:47 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_guard_checker(t_data *data)
{
	ft_check_death(data);
	pthread_mutex_lock(&data->check_death);
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(&data->check_death);
		return (2);
	}
	pthread_mutex_unlock(&data->check_death);
	return (0);
}

static int	ft_check_death2(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&(data->check_meal));
	if (ft_get_time() - philo[(i)].last_meal >= data->schedule.time_to_die)
	{
		ft_logs(philo, (i + 1), "has died");
		pthread_mutex_lock(&data->check_death);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->check_death);
		pthread_mutex_unlock(&(data->check_meal));
		return (2);
	}
	pthread_mutex_unlock(&(data->check_meal));
	return (0);
}

void	ft_guard(t_data *data)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&data->check_ate);
		if (data->all_ate)
		{
			pthread_mutex_unlock(&data->check_ate);
			break ;
		}
		pthread_mutex_unlock(&data->check_ate);
		if (ft_guard_checker(data) == 2)
			break ;
		i = 0;
		while (data->schedule.num_of_eating != -1 && i < data->nb_philos
			&& data->philos[i].nb_meals >= data->schedule.num_of_eating)
			i++;
		pthread_mutex_lock(&data->check_ate);
		if (i == data->nb_philos)
			data->all_ate = 1;
		pthread_mutex_unlock(&data->check_ate);
	}
}

void	ft_check_death(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_lock(&data->check_death);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->check_death);
			break ;
		}
		pthread_mutex_unlock(&data->check_death);
		if (ft_check_death2(philo, data, i) == 2)
			break ;
		usleep(100);
	}
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->fork_left]));
	ft_logs(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->data->forks[philo->fork_right]));
	ft_logs(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->data->check_meal));
	ft_logs(philo, philo->id, "is eating");
	philo->last_meal = ft_get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&(philo->data->check_meal));
	ft_kill_philo(philo->schedule->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_left]));
	pthread_mutex_unlock(&(philo->data->forks[philo->fork_right]));
}
