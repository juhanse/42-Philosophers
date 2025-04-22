/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/22 12:03:04 by juhanse          ###   ########.fr       */
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
	long long		start_time;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	print;
	pthread_mutex_t	check_death;
	pthread_mutex_t	check_meal;
}	t_data;

// UTILS
int			ft_atoi(const char *str);
long long	get_time(void);

// INIT
int			ft_init_data(t_data *data, char **argv);
int			ft_init_philo(t_data *data);
int			ft_init_mutex(t_data *data);

// ROUTINE
int			ft_routine(t_data *data);

// EXIT
void		ft_destroy_mutex(t_data *data);

void		ft_debug(t_data *data);

#endif
