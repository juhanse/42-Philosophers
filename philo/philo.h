/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/04/23 23:05:14 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILO 200
# define ERR_ARGS "Error\nInvalid arguments\n"
# define ERR_LIMITS "Error\nPhilosophers limits\n"
# define ERR_MALLOC "Error\nAllocation failed\n"

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	bool			is_eating;
	pthread_t		thread;
	long long		last_eat;
	struct s_data	*data;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	fork_left;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				philo_eat;
	long long		t_start;
	int				stop;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_dead;
}	t_data;

// UTILS
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	ft_get_time(void);
void		ft_waiting(int ms);
void		ft_logs(t_data *data, int id, char *msg);

// INIT
void		ft_destroy_mutex(t_data *data);
int			ft_init_data(t_data *data, char **argv);
int			ft_init_philo(t_data *data);
int			ft_init_mutex(t_data *data);

// ROUTINE
int			ft_routine(t_data *data);
void		*ft_threads(void *arg);

// PHILO
void		ft_guard(t_data *data);
void		ft_check_death(t_data *data);
void		ft_take_forks(t_philo *philo);

#endif
