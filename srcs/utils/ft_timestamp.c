/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timestamp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:46:02 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/09 11:35:48 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_waiting(t_data *data, int ms)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start < ms))
	{
		if (ft_get_stop(data) == 1)
			break ;
		usleep(50);
	}
}
