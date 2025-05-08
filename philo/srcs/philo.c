/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 19:57:54 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_one_philo(t_data *data)
{
	pthread_mutex_lock(data->philo->fork_left);
	ft_logs(&data->philo[0], "has taken a fork");
	pthread_mutex_unlock(data->philo->fork_left);
	ft_logs(&data->philo[0], "has taken a fork");
	ft_waiting(data, data->t_die);
	ft_logs(&data->philo[0], "dead");
	return (0);
}

int	ft_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->m_stop);
	stop = data->stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stop);
}

void	*ft_monitoring(void *arg)
{
	int			i;
	t_data		*data;
	t_philo		*philo;

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
				ft_logs(philo, "died");
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

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_waiting(philo->data, philo->data->t_eat / 2);
	while (!ft_should_stop(philo->data))
	{
		//printf("STOP: %d\n", ft_should_stop(philo->data)); // DELETE
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
