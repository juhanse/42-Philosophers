/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/13 00:42:01 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_one_philo(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(data->philo->fork_left);
	ft_logs(&data->philo[0], "has taken a fork");
	pthread_mutex_unlock(data->philo->fork_left);
	ft_waiting(data, data->t_die);
	ft_logs(&data->philo[0], "dead");
	return (0);
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		ft_logs(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		ft_logs(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		ft_logs(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		ft_logs(philo, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_eat);
	philo->last_eat = ft_get_time();
	philo->nb_meals++;
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
