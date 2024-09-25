#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

#define RESET	"\033[0m"
#define RED	"\033[1;31m"
#define WHITE	"\033[1;37m"
#define GREEN	"\033[1;32m"

typedef	struct	s_table t_table;

// typedef struct  s_fork
// {
// 	pthread_mutex_t fork;
// 	int             fork_id;
// }	t_fork;

typedef struct	s_philo
{
	int		philo_id;
	int     left_fork_id;
	int		right_fork_id;
	bool	is_dead;
	long	last_mealtime;
	pthread_mutex_t	meal_monitor;
	pthread_mutex_t	dead_monitor;
	pthread_t	thread;
  t_table *table;
}	t_philo;

struct	s_table
{
	int	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	meal_counter;
	long	start_time;
	bool	is_end;
	pthread_mutex_t write;
	pthread_mutex_t forks[250];
	pthread_t	death_thread;
	t_philo	philos[250];
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
void	ft_thread(pthread_t *thread, int flag, void *func(void *));
void	ft_mutex(pthread_mutex_t *mutex, int flag);
void	error_exit(const char *message);
// void	*ft_malloc(size_t bytes);
long  gettime_ms(void);
void print_state(long timestamp, int id, const char *state, t_table *table);
void 	precise_sleep(long milisec);
// bool  philo_died(t_philo *philos);

// debug
void d(const char *msg);

// *** init.c ***
void	data_init(t_table *table);

// *** parsing.c ***
void	parse_input(t_table *table, char *argv[]);

void	party(t_table *table);

void  clean(t_table *table);

// *** monitor.c ***
void	*monitor_philo_life(void *info);

// void	assign_bool(t_table *table, bool *dst, bool src);
// void	assign_value(t_table *table, long *dst, long src);