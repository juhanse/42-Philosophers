/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:40:17 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 21:45:39 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->check_meal);
	pthread_mutex_destroy(&data->check_ate);
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&data->print, NULL))
		return (1);
	if (pthread_mutex_init(&data->check_death, NULL))
		return (1);
	if (pthread_mutex_init(&data->check_meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->check_ate, NULL))
		return (1);
	return (0);
}

int	ft_init_philo(t_data *data)
{
	int	i;

	i = -1;
	if (ft_init_mutex(data))
		return (1);
	while (++i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_meals = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].fork_left = i;
		data->philos[i].fork_right = (i + 1) % data->nb_philos;
		data->philos[i].schedule = &data->schedule;
		data->philos[i].data = data;
	}
	return (0);
}

int	ft_init_data(t_data *data, char **argv)
{
	if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (1);
	data->nb_philos = ft_atoi(argv[1]);
	data->schedule.time_to_die = ft_atoi(argv[2]);
	data->schedule.time_to_eat = ft_atoi(argv[3]);
	data->schedule.time_to_sleep = ft_atoi(argv[4]);
	if (data->nb_philos < 1 || data->nb_philos > 200
		|| data->schedule.time_to_die < 0 || data->schedule.time_to_eat < 0
		|| data->schedule.time_to_sleep < 0)
		return (printf(ERR_ARGS), 1);
	if (argv[5])
	{
		data->schedule.num_of_eating = ft_atoi(argv[5]);
		if (data->schedule.num_of_eating <= 0)
			return (printf(ERR_ARGS), 1);
	}
	else
		data->schedule.num_of_eating = -1;
	if (data->nb_philos == 1)
		return (printf("0 1 has taken a fork\n"), printf("0 1 has died\n"), 0);
	if (ft_init_philo(data))
		return (1);
	return (0);
}
