/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:40:17 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/06 15:02:44 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_eat, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_stop, NULL))
		return (1);
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (1);
	return (0);
}

int	ft_init_philo(t_data *data)
{
	int	i;

	i = -1;
	if (ft_init_mutex(data))
		return (1);
	data->t_start = ft_get_time();
	while (++i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = data->t_start;
		data->philo[i].fork_right = NULL;
		data->philo[i].data = data;
		data->philo[i].times_eaten = 0;
		pthread_mutex_init(&(data->philo[i].fork_left), NULL);
		if (i == data->nb_philos - 1)
			data->philo[i].fork_right = &data->philo[0].fork_left;
		else
			data->philo[i].fork_right = &data->philo[i + 1].fork_left;
		if (pthread_create(&data->philo[i].thread, NULL, ft_philo, \
			(void *)&data->philo[i]) != 0)
			return (-1);
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
	return (0);
}
