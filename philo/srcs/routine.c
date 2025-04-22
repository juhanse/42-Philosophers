/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 14:28:11 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->stop_simulation)
	{
		pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
		ft_logs(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
		ft_logs(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->check_meal);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->data->check_meal);
		ft_logs(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
		pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
		philo->nb_meals++;
		if (philo->data->num_of_eating != 0 && \
			philo->nb_meals >= philo->data->num_of_eating)
			break ;
		ft_logs(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		ft_logs(philo, "is thinking");
	}
	return (NULL);
}

int	ft_routine(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, &ft_threads, &data->philos[i]))
		{
			return (1);
		}
	}
	ft_destroy_mutex(data);
	return (0);
}
