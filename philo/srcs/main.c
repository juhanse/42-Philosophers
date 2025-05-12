/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:26:15 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/13 00:26:21 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	ft_parsing(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (1);
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_parsing(argc, argv))
		return (printf(ERR_ARGS), 1);
	data = (t_data){0};
	if (ft_init_data(&data, argv))
		return (printf(ERR_INIT), ft_free(&data), 1);
	if (data.nb_philos == 1)
		return (ft_one_philo(&data), ft_free(&data), 1);
	if (ft_start_simulation(&data))
		return (printf(ERR_INIT), ft_free(&data), 1);
	ft_free(&data);
	return (0);
}
