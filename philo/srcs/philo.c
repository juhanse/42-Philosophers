/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 23:18:02 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->m_stop);
	pthread_mutex_lock(&philo->data->m_dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		pthread_mutex_unlock(&philo->data->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (0);
}

void	*ft_check_death(void *phi)
{
	t_philo		*philo;
	long long	last;

	philo = (t_philo *)phi;
	ft_waiting(philo->data->t_die + 1);
	pthread_mutex_lock(&philo->data->m_eat);
	last = philo->last_eat;
	if (timestamp() - last > (long)(philo->data->t_die) && !ft_is_dead(philo, 0) && philo->id != 0)
	{
		pthread_mutex_unlock(&philo->data->m_eat);
		pthread_mutex_lock(&philo->data->m_stop);
		if (philo->data->stop)
		{
			pthread_mutex_unlock(&philo->data->m_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->m_stop);
		ft_is_dead(philo, 1);
		ft_logs(philo->data, philo->id, "died");
		// free ?
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	return (NULL);
}

void	*ft_philo(void *phi)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	t;

	philo = (t_philo *)phi;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_waiting(data->t_eat / 2);
	while (!ft_is_dead(philo, 0))
	{
		pthread_create(&t, NULL, ft_check_death, phi);
		philo_eat(philo);
		pthread_detach(t);
		if (philo->times_eaten == philo->data->n_eat && philo->data->n_eat != -1)
		{
			ft_is_dead(philo, 1);
			return (NULL);
		}
	}
	return (NULL);
}
