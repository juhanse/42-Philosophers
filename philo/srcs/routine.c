/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 12:45:17 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_threads(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;

	if (philo->id % 2 == 0)
		usleep(1000);
	while (!data->stop_simulation)
	{
		pthread_mutex_lock(&data->forks[philo->fork_left]);
		pthread_mutex_lock(&data->print);
		ft_logs(get_time() - data->start_time, philo->id, "has taken a fork");
		pthread_mutex_unlock(&data->print);
		pthread_mutex_lock(&data->forks[philo->fork_right]);
		pthread_mutex_lock(&data->print);
		ft_logs(get_time() - data->start_time, philo->id, "has taken a fork");
		pthread_mutex_unlock(&data->print);
		pthread_mutex_lock(&data->check_meal);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&data->check_meal);
		pthread_mutex_lock(&data->print);
		ft_logs(get_time() - data->start_time, philo->id, "is eating");
		pthread_mutex_unlock(&data->print);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(&data->forks[philo->fork_left]);
		pthread_mutex_unlock(&data->forks[philo->fork_right]);
		philo->nb_meals++;
		if (data->num_of_eating && philo->nb_meals >= data->num_of_eating)
			break;
		pthread_mutex_lock(&data->print);
		ft_logs(get_time() - data->start_time, philo->id, "is sleeping");
		pthread_mutex_unlock(&data->print);
		usleep(data->time_to_sleep * 1000);
		pthread_mutex_lock(&data->print);
		ft_logs(get_time() - data->start_time, philo->id, "is thinking");
		pthread_mutex_unlock(&data->print);
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
