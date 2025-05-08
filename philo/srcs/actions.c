/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 12:12:26 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_should_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->m_stop);
	stop = data->stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stop);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->is_eating = true;
	philo->times_eaten++;
	philo->last_eat = ft_get_time();
	ft_logs(philo->data, philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->m_eat);
	ft_waiting(philo->data->t_eat);
	pthread_mutex_lock(&philo->data->m_eat);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->data->m_eat);
	ft_sleep(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_logs(philo->data, philo->id, "is sleeping");
	ft_think(philo);
}

void	ft_think(t_philo *philo)
{
	ft_logs(philo->data, philo->id, "is thinking");
}

void	ft_routine(t_philo *philo)
{
	// TODO
}
