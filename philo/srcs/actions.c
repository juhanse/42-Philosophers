/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 11:40:20 by juhanse          ###   ########.fr       */
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
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
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
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	ft_waiting(1);
	ft_sleep(philo);
}

void	ft_sleep(t_philo *philo)
{
	if (ft_should_stop(philo->data))
		return ;
	ft_logs(philo->data, philo->id, "is sleeping");
	ft_waiting(philo->data->t_sleep);
	ft_think(philo);
}

void	ft_think(t_philo *philo)
{
	if (ft_should_stop(philo->data))
		return ;
	ft_logs(philo->data, philo->id, "is thinking");
}

void	ft_routine(t_philo *philo)
{
	if (ft_should_stop(philo->data))
		return ;
	if (philo->id % 2 == 0)
	{
		philo->fork_left = philo->fork_right;
		philo->fork_right = &philo->fork_left;
	}
	else
	{
		philo->fork_left = &philo->fork_left;
		philo->fork_right = philo->fork_right;
	}
	pthread_mutex_lock(philo->fork_left);
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	ft_logs(philo->data, philo->id, "has taken a fork");
	if (philo->data->nb_philos == 1)
	{
		ft_waiting(philo->data->t_die * 2);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	pthread_mutex_lock(philo->fork_right);
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return ;
	}
	ft_logs(philo->data, philo->id, "has taken a fork");
	ft_eat(philo);
}
