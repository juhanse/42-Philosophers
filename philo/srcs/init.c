/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:40:17 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/17 16:24:26 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (1);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->nb_philos < 1 || data->nb_philos > 200
		|| data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (1);
	if (data->nb_philos == 1)
		return (printf("0 1 has taken a fork\n"), printf("0 1 has died\n"), 1);
	if (argv[5])
		data->num_of_eating = ft_atoi(argv[5]);
	if (init_philo(data))
		return (1);
	return (0);
}
