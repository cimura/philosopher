/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:05:32 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 20:06:21 by sshimura         ###   ########.fr       */
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

typedef struct s_end
{
	bool			is_end;
	pthread_mutex_t	lock;
}	t_end;

typedef struct s_meal_counter
{
	long long		meal_counter;
	pthread_mutex_t	lock;
}	t_meal_counter;

typedef struct s_hungry
{
	int				hungry_id;
	pthread_mutex_t	lock;
}	t_hungry;

typedef struct s_last_mealtime
{
	long long		last_mealtime;
	pthread_mutex_t	lock;	
}	t_last_mealtime;

typedef struct s_forks
{
	bool			clean;
	// int				id;
	pthread_mutex_t	lock;
}	t_forks;

typedef struct s_que
{
	int	que[201];
	int	head;
	int	tail;
	pthread_mutex_t	lock;
}	t_que;

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	t_last_mealtime	_time;
	t_meal_counter	_meal;
	pthread_t		thread;
	t_table			*table;
}	t_philo;

struct	s_table
{
	int				philo_nbr;
	t_hungry		_hunger;
	t_que			que;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		nbr_limit_meals;
	long long		start_time;
	t_end			_end;
	pthread_mutex_t	write;
	// pthread_mutex_t	*forks;
	t_forks			*forks;
	pthread_t		death_detector;
	t_philo			*philos;
};

enum	e_mutex_flag
{
	INIT = 42,
	DESTROY,
	LOCK,
	UNLOCK,
};

enum	e_err_flag
{
	ERR_STATUS = -42,
	PARSE_ERR,
	THREAD_ERR,
	JOIN_ERR,
	DEAD,
	STARVATION
};

// *** utils.c ***
void		print_error(const char *message);
long long	gettime_ms(void);
void		print_state(int id, const char *state, t_table *table);
void		precise_sleep(t_philo *philos, long long milisec);
void		ft_mutex(pthread_mutex_t *mutex, int flag);

void	enque(t_table *table, int id);
int	deque(t_table *table, int id);

// *** print.c ***
void		print_error(const char *message);
void		print_state(int id, const char *state, t_table *table);

// *** init.c ***
int			data_init(t_table *table);

// *** parsing.c ***
int			parse_input(t_table *table, char *argv[]);

// *** threads.c ***
int			create_threads(t_table *table);
int			join_threads(t_table *table);

// *** action.c ***
void		taking_forks(t_philo *philos);
void		eating(t_philo *philos);
void		thinking(t_philo *philos);
void		sleeping(t_philo *philos);

// *** monitor.c ***
void		*monitor_philo_life(void *info);
bool		is_end(t_philo *philos);

#endif
