/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:01:04 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 12:21:43 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_threads)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(data->monitoring, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_stop);
	free(data->philo);
	free(data->forks);
}
