/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:22:49 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/08 12:19:30 by juhanse          ###   ########.fr       */
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
	int				times_eaten;
	bool			is_eating;
	long long		last_eat;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	struct s_data	*data;
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
void		ft_waiting(int ms);
void		ft_logs(t_data *data, int id, char *msg);
void		ft_free(t_data *data);
void		*ft_malloc(t_data *data, size_t size);

// INIT
int			ft_init_data(t_data *data, char **argv);
int			ft_init_philo(t_data *data);
int			ft_init_mutex(t_data *data);
int			ft_start_simulation(t_data *data);

// ACTIONS
int			ft_should_stop(t_data *data);
void		ft_routine(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

// PHILO
void		ft_monitoring(t_data *data);
bool		ft_is_stop(t_philo *philo);
void		*ft_check_death(void *phi);
void		*ft_philo(void *phi);

#endif
