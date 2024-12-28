/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:05:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/28 16:27:50 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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

typedef struct s_table	t_table;
typedef struct s_philo
{
	int				philo_id;
	long long		last_mealtime;
	long long		meal_counter;
	pid_t			pid;
	sem_t			*meal_lock;
	pthread_t		death_detector;
	t_table			*table;
}	t_philo;

struct	s_table
{
	int				philo_nbr;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		nbr_limit_meals;
	long long		start_time;
	bool			is_end;
	bool			is_dead;
	char			**name_ptr;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*write_lock;
	sem_t			*meal_counter_lock;
	pthread_t		death_waiter;
	t_philo			*philos;
};

enum	e_err_flag
{
	ERR_STATUS = -5,
	PARSE_ERR,
	THREAD_ERR,
	JOIN_ERR,
	DEAD
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
int			create_philos(t_table *table);

// *** action.c ***
int			taking_forks(t_table *table, t_philo *philos);
int			eating(t_table *table, t_philo *philos);
void		thinking(t_philo *philos);
void		sleeping(t_philo *philos);

// *** monitor.c ***
void		*monitor_philo_life(void *info);

// *** string_utils.c ***
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int nun);

// *** clean.c ***
void		clean_name(t_table *table);
void		clean_sem_meal_lock(t_table *table);
void		clean(t_table *table);

#endif
