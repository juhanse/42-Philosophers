/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 12:19:02 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_monitoring(t_data *data)
{
	// TODO
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
	t_philo		*philo;

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
