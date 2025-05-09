/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:19 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/09 11:35:57 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_logs(t_philo *philo, char *msg)
{
	long long	time;

	time = ft_get_time() - philo->data->t_start;
	pthread_mutex_lock(&philo->data->m_print);
	if (ft_get_stop(philo->data) != 1)
		printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->m_print);
}
