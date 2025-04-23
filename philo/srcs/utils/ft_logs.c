/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:19 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 23:22:03 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_logs(t_data *data, int id, char *msg)
{
	long long	time;

	pthread_mutex_lock(&data->m_print);
	time = ft_get_time();
	printf("%lld | %d | %s\n", time - data->t_start, id, msg);
	pthread_mutex_unlock(&data->m_print);
}
