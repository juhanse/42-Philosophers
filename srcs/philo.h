/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/15 20:00:37 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eating;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long			last_meal;
	int				fork_left;
	int				fork_right;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

// UTILS
int		ft_atoi(const char *str);

void	ft_init(t_philo *philo, char **argv, int hasTimer);

#endif
