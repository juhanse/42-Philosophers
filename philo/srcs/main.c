/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 12:15:53 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_debug(t_data *data)
{
	printf("nb_philos: [%d]\n", data->nb_philos);
	printf("time_to_die: [%d]\n", data->time_to_die);
	printf("time_to_eat: [%d]\n", data->time_to_eat);
	printf("time_to_sleep: [%d]\n", data->time_to_sleep);
	printf("num_of_eating: [%d]\n", data->num_of_eating);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (printf(ERR_ARGS), 1);
	data = (t_data){0};
	if (ft_init_data(&data, argv))
		return (1); 
	ft_debug(&data);
	if (ft_routine(&data))
		return (1);
	ft_destroy_mutex(&data);
	return (0);
}
