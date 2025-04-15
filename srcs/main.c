/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 20:01:14 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_philo *philo, char **argv, int hasTimer)
{
	*philo = (t_philo){0};
	philo->data->nb_philos = ft_atoi(argv[1]);
	philo->data->time_to_die = ft_atoi(argv[2]);
	philo->data->time_to_eat = ft_atoi(argv[3]);
	philo->data->time_to_sleep = ft_atoi(argv[4]);
	if (hasTimer)
		philo->data->num_of_eating = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc == 4)
		ft_init(&philo, argv, 0);
	else if (argc == 5)
		ft_init(&philo, argv, 1);
	else
		printf("Invalid arguments\n");
	return (0);
}
