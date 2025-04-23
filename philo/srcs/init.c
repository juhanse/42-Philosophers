/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:40:17 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 23:05:26 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->philo[i].fork_left);
	if (data->philo)
		free(data->philo); // OUPS
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_dead);
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

int	ft_init_data(t_data *data, char **av)
{
	data->philo_eat = 0;
	data->nb_philos = ft_atoi(av[1]);
	if (data->nb_philos < 1 || data->nb_philos > MAX_PHILO)
		return (printf(ERR_LIMITS), 1);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_eat = -1;
	data->stop = 0;
	if (av[5])
		data->n_eat = ft_atoi(av[5]);
	if (data->t_die < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || (av[5] && data->n_eat < 1))
		return (printf(ERR_ARGS), 1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philo)
		return (printf(ERR_MALLOC), 1);
	if (ft_init_philo(data))
		return (1);
	return (0);
}
