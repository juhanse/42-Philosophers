/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/02/12 18:32:58 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_init(t_philo *philo, char **argv)
{
	*philo = (t_philo){0};
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc == 4)
		ft_init(&philo, argv);
	else if (argc == 5)
		ft_init(&philo, argv);
	else
		printf("Invalid arguments\n");
	return (0);
}
