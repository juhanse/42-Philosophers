/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:19 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/06 15:08:27 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_logs(t_data *data, int id, char *msg)
{
	long long	time;

	if (ft_should_stop(data))
		return ;
	pthread_mutex_lock(&data->m_print);
	if (ft_should_stop(data))
	{
		pthread_mutex_unlock(&data->m_print);
		return ;
	}
	time = ft_get_time();
	printf("%lld %d %s\n", time - data->t_start, id, msg);
	pthread_mutex_unlock(&data->m_print);
}
