/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 21:51:04 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_threads2(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->check_meal));
	if (data->schedule.num_of_eating != -1
		&& philo->nb_meals >= data->schedule.num_of_eating)
	{
		pthread_mutex_unlock(&(data->check_meal));
		return (2);
	}
	pthread_mutex_unlock(&(data->check_meal));
	ft_take_forks(philo);
	pthread_mutex_lock(&data->check_ate);
	if (data->all_ate)
	{
		pthread_mutex_unlock(&data->check_ate);
		return (2);
	}
	pthread_mutex_unlock(&data->check_ate);
	return (0);
}

void	*ft_threads(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		pthread_mutex_lock(&data->check_death);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->check_death);
			break ;
		}
		pthread_mutex_unlock(&data->check_death);
		if (ft_threads2(data, philo) == 2)
			break ;
		ft_afk(philo);
	}
	return (NULL);
}

int	ft_routine(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, \
		ft_threads, &(philo[i])))
		{
			pthread_mutex_lock(&data->check_death);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->check_death);
			while (--i >= 0)
				pthread_join(philo[i].thread_id, NULL);
			return (1);
		}
		pthread_mutex_lock(&data->check_meal);
		philo[i].last_meal = ft_get_time();
		pthread_mutex_unlock(&data->check_meal);
	}
	ft_guard(data);
	ft_destroy_mutex(data);
	return (0);
}
