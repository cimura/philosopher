/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:05:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 13:40:45 by sshimura         ###   ########.fr       */
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
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"

# define ERROR_STATUS -1

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				philo_id;
	int				left_fork_id;
	int				right_fork_id;
	bool			is_dead;
	long long		last_mealtime;
	pid_t			pid;
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
	char			*sem_name;
	sem_t			*sem;
	pthread_t		death_thread;
	t_philo			philos[201];
};

enum	e_flag
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE
};

// *** utils.c ***
void		print_error(const char *message);
long long	gettime_ms(void);
void		print_state(int id, const char *state, t_table *table);
void		precise_sleep(t_philo *philos, long long milisec);
void		ft_mutex(pthread_mutex_t *mutex, int flag);

// *** init.c ***
int			data_init(t_table *table);
int			create_death_thread(t_table *table);

// *** parsing.c ***
int			parse_input(t_table *table, char *argv[]);

// *** process.c ***
void		simulation(t_table *table);
int			wait_all_philos(t_table *table);

// *** action.c ***
int			taking_forks(t_philo *philos);
int			eating(t_philo *philos);
void		thinking(t_philo *philos);
void		sleeping(t_philo *philos);

// *** monitor.c ***
void		*monitor_philo_life(void *info);
bool		is_dead(t_philo *philos);
bool		check_full(t_philo *philos);

// *** clean.c ***
void		clean(t_table *table);

#endif
