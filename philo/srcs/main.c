/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 21:36:24 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->check_death);
	pthread_mutex_destroy(&data->check_meal);
	pthread_mutex_destroy(&data->check_ate);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf(ERR_ARGS), 1);
	data = (t_data){0};
	if (ft_init_data(&data, argv))
		return (1);
	if (ft_routine(&data))
		return (1);
	return (0);
}
