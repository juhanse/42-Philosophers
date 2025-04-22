/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 12:02:04 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_create_threads(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].last_meal = data->start_time;
		// if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]))
		// 	return (1);
		usleep(100);
	}
	return (0);
}

int	ft_routine(t_data *data)
{
	if (ft_create_threads(data))
		return (1);
	return (0);
}
