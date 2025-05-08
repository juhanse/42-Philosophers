/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:07:36 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 11:42:00 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->m_stop);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
		return (pthread_mutex_unlock(&philo->data->m_stop), 1); 
	pthread_mutex_unlock(&philo->data->m_stop);
	return (0);
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
	t_data		*data;
	pthread_t	t;

	philo = (t_philo *)phi;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_waiting(data->t_eat / 2);
	while (!ft_is_dead(philo, 0))
	{
		ft_routine(philo);
		if (philo->times_eaten == philo->data->n_eat \
			&& philo->data->n_eat != -1)
		{
			ft_is_dead(philo, 1);
			break ;
		}
	}
	return (NULL);
}
