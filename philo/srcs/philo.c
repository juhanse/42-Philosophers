/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 17:06:05 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->m_stop);
	stop = data->stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stop);
}

void	*ft_monitoring(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	int			i;

	data = (t_data *)arg;
	while (!ft_should_stop(data))
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			philo = &data->philo[i];
			pthread_mutex_lock(&data->m_eat);
			if ((ft_get_time() - philo->last_eat) > data->t_die)
			{
				ft_print(data, philo->id, "died");
				pthread_mutex_lock(&data->m_stop);
				data->stop = 1;
				pthread_mutex_unlock(&data->m_stop);
				pthread_mutex_unlock(&data->m_eat);
				return (NULL);
			}
			pthread_mutex_unlock(&data->m_eat);
		}
		usleep(1000);
	}
	return (NULL);
}

bool	ft_is_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_stop);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_stop);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->m_stop);
	return (false);
}

void	*ft_check_death(void *phi)
{
	t_philo		*philo;
	long long	last;

	philo = (t_philo *)phi;
	while (!ft_should_stop(philo->data))
	{
		pthread_mutex_lock(&philo->data->m_eat);
		last = philo->last_eat;
		if (ft_get_time() - last > (long)(philo->data->t_die) && \
		!ft_is_dead(philo, 0) && philo->id != 0)
		{
			pthread_mutex_unlock(&philo->data->m_eat);
			ft_logs(philo->data, philo->id, "died");
			ft_is_dead(philo, 1);
			break ;
		}
		pthread_mutex_unlock(&philo->data->m_eat);
	}
	return (NULL);
}

void	*ft_philo(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	if (philo->id % 2 == 0)
		ft_waiting(philo->data->t_eat / 2);
	while (!ft_is_stop(philo))
	{
		ft_routine(philo);
		if (philo->times_eaten == philo->data->n_eat \
			&& philo->data->n_eat != -1)
		{
			philo->data->stop = 1;
			break ;
		}
	}
	return (NULL);
}
