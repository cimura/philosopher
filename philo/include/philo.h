/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:05:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 01:37:40 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"

# define PARSE_ERR		2
# define THREAD_ERR		3
# define JOIN_ERR		4

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_mealtime;
	pthread_mutex_t	meal_monitor;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

struct	s_table
{
	int				philo_nbr;
	long long		meal_counter;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		nbr_limit_meals;
	long long		start_time;
	bool			is_end;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_t		death_detector;
	t_philo			*philos;
};

enum	e_flag
{
	INIT = 42,
	DESTROY,
	LOCK,
	UNLOCK,
};

// *** utils.c ***
void		print_error(const char *message);
long long	gettime_ms(void);
void		print_state(int id, const char *state, t_table *table);
void		precise_sleep(t_philo *philos, long long milisec);
void		ft_mutex(pthread_mutex_t *mutex, int flag);

// *** init.c ***
int			data_init(t_table *table);

// *** parsing.c ***
int			parse_input(t_table *table, char *argv[]);

// *** party.c ***
int			create_philos(t_table *table);
int			join_threads(t_table *table);

// *** action.c ***
void		taking_forks(t_philo *philos);
void		eating(t_philo *philos);
void		thinking(t_philo *philos);
void		sleeping(t_philo *philos);

// *** monitor.c ***
void		*monitor_philo_life(void *info);
bool		is_dead(t_philo *philos);
bool		check_full(t_philo *philos);

#endif
