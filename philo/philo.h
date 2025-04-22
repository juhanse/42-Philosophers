/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 11:31:13 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_ARGS "Error\nBad arguments\n"

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

// UTILS
int			ft_atoi(const char *str);
long long	get_time(void);

int			ft_init_data(t_data *data, char **argv);
int			ft_init_philo(t_data *data);
int			ft_init_mutex(t_data *data);

#endif
