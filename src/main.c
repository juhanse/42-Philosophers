/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/02/12 18:41:28 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_init(t_philo *philo, char **argv, int hasTimer)
{
	*philo = (t_philo){0};
	philo->numbers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (hasTimer)
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
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
