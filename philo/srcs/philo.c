/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/09 14:48:00 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_check_death(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->data->m_eat);
	now = ft_get_time();
	if (now - philo->last_eat > philo->data->t_die)
	{
		ft_logs(philo, "died");
		pthread_mutex_unlock(&philo->data->m_eat);
		ft_stop_simulation(philo->data);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	return (0);
}

static int	ft_check_meals(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->data->m_eat);
	if (philo->data->n_eat > 0 && philo->nb_meals >= philo->data->n_eat)
		ret = 1;
	pthread_mutex_unlock(&philo->data->m_eat);
	return (ret);
}

int	ft_get_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->m_stop);
	stop = data->stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stop);
}

void	*ft_monitoring(void *arg)
{
	int		i;
	int		meals;
	t_data	*data;

	data = (t_data *)arg;
	while (!ft_get_stop(data))
	{
		i = -1;
		meals = 0;
		while (++i < data->nb_philos)
		{
			if (ft_check_death(&data->philo[i]))
				return (NULL);
			if (ft_check_meals(&data->philo[i]))
				meals++;
		}
		if (data->n_eat > 0 && meals == data->nb_philos)
		{
			ft_stop_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_waiting(philo->data, philo->data->t_eat / 2);
	while (!ft_get_stop(philo->data))
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
