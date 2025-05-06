/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:01:04 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/06 12:47:22 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	if (data->philo)
	{
		while (++i < data->nb_philos)
		{
			pthread_join(data->philo[i].thread, NULL);
			pthread_mutex_destroy(&(data->philo[i].fork_left));
		}
		free(data->philo);
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_dead);
}
