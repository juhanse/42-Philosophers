/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:54:09 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 12:29:41 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_threads()
{
	printf("TEST\n");
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
