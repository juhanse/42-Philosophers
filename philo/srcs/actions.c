/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/06 14:44:32 by juhanse          ###   ########.fr       */
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

void	ft_eat(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
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
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
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
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork_right;
		second_fork = &philo->fork_left;
	}
	else
	{
		first_fork = &philo->fork_left;
		second_fork = philo->fork_right;
	}
	if (ft_should_stop(philo->data))
		return ;
	pthread_mutex_lock(first_fork);
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	ft_logs(philo->data, philo->id, "has taken a fork");
	if (philo->data->nb_philos == 1)
	{
		ft_waiting(philo->data->t_die * 2);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	if (ft_should_stop(philo->data))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	ft_logs(philo->data, philo->id, "has taken a fork");
	ft_eat(philo, first_fork, second_fork);
}
