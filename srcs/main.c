/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/16 23:25:34 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_philo *philo, char **argv)
{
	if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
		return (1);
	philo->data->nb_philos = ft_atoi(argv[1]);
	philo->data->time_to_die = ft_atoi(argv[2]);
	philo->data->time_to_eat = ft_atoi(argv[3]);
	philo->data->time_to_sleep = ft_atoi(argv[4]);
	if (philo->data->nb_philos < 1 || philo->data->nb_philos > 200
		|| philo->data->time_to_die < 0 || philo->data->time_to_eat < 0
		|| philo->data->time_to_sleep < 0)
		return (1);
	if (philo->data->nb_philos == 1)
		return (printf("0 1 has taken a fork\n"), printf("0 1 has died\n"), 1);
	if (argv[5])
		philo->data->num_of_eating = ft_atoi(argv[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
		return (printf("not the mount of args asked for, argc : %d\n", argc), 1);
	if (ft_init_philo(&philo, argv))
		return (1);
	return (0);
}
