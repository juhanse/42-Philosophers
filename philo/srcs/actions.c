/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 18:00:11 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	ft_logs(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	ft_logs(philo, "has taken a fork");
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->last_eat = ft_get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->m_eat);
	ft_logs(philo, "is eating");
	ft_waiting(philo->data, philo->data->t_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	ft_sleep(t_philo *philo)
{
	ft_logs(philo, "is sleeping");
	ft_waiting(philo->data, philo->data->t_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_logs(philo, "is thinking");
}
