/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:47:26 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 20:50:17 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_kill_philo(long long time, t_philo *philo)
{
	long long	i;

	i = ft_get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->data->check_death);
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&philo->data->check_death);
			break ;
		}
		pthread_mutex_unlock(&philo->data->check_death);
		if ((ft_get_time() - i) >= time)
			break ;
		usleep(50);
	}
}
