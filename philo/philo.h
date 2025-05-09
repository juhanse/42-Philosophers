/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/09 14:28:45 by juhanse          ###   ########.fr       */
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

# define MAX_PHILO 	200
# define ERR_ARGS 	"Error\nInvalid arguments\n"
# define ERR_LIMITS "Error\nPhilosophers limits\n"
# define ERR_MALLOC "Error\nAllocation failed\n"
# define ERR_INIT	"Error\nInitialisation failed\n"

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	long long		t_start;
	int				stop;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				nb_threads;
	t_philo			*philo;
	pthread_t		monitoring;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_stop;
}	t_data;

// UTILS
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	ft_get_time(void);
void		ft_waiting(t_data *data, int ms);
void		ft_logs(t_philo *philo, char *msg);
void		ft_free(t_data *data);

// INIT
int			ft_init_data(t_data *data, char **argv);
int			ft_init_philo(t_data *data);
int			ft_init_mutex(t_data *data);
int			ft_start_simulation(t_data *data);

// PHILO
int			ft_one_philo(t_data *data);
int			ft_get_stop(t_data *data);
void		*ft_monitoring(void *arg);
void		*ft_routine(void *arg);

// ACTIONS
int			ft_one_philo(t_data *data);
void		ft_take_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

#endif
