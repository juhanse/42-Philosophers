/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:41:19 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 21:56:25 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	ft_logs(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->check_death);
	if (!philo->data->stop_simulation)
		printf("%lld %d %s\n", ft_get_time() - philo->data->start_time, id,
			str);
	pthread_mutex_unlock(&philo->data->check_death);
	pthread_mutex_unlock(&philo->data->print);
	return ;
}

void	ft_afk(t_philo *philo)
{
	ft_logs(philo, philo->id, "is sleeping");
	ft_kill_philo(philo->schedule->time_to_sleep, philo);
	ft_logs(philo, philo->id, "is thinking");
}
