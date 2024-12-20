/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:05:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 12:21:33 by cimy             ###   ########.fr       */
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
# include <signal.h>

# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"

# define ERROR_STATUS -1

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				philo_id;
	//bool			is_dead;
	long long		last_mealtime;
	pid_t			pid;
	sem_t			*meal_lock;
	pthread_t		death_detector;
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
	bool			is_dead;
	// from 1
	//long long		last_mealtime[202];
	//sem_t			*meal[202];
	sem_t			*forks;
	sem_t			*death;
	sem_t			*write_lock;
	pthread_t		death_waiter;
	//pthread_t		meal_updater[201];
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
void		precise_sleep(long long milisec);

// *** init.c ***
int			data_init(t_table *table);

// *** parsing.c ***
int			parse_input(t_table *table, char *argv[]);

// *** process.c ***
void			simulation(t_table *table, t_philo *philo);
int			wait_all_philos(t_table *table);

// *** action.c ***
int			taking_forks(t_table *table, t_philo *philos);
int			eating(t_table *table, t_philo *philos);
void		thinking(t_philo *philos);
void		sleeping(t_philo *philos);

// *** monitor.c ***
void		*monitor_philo_life(void *info);
void		send_kill_signal(t_table *table);

// *** clean.c ***
void		clean(t_table *table);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
#endif
