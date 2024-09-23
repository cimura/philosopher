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

typedef struct  s_fork
{
	pthread_mutex_t fork;
	int             fork_id;
}	t_fork;

typedef struct	s_philo
{
	int		philo_id;
	long	meal_counter;
	bool	is_dead;
	long	last_mealtime;
	pthread_mutex_t	monitor;
	t_fork	left_fork;
	t_fork	right_fork;
	pthread_t	philosopher;
  t_table *table;
}	t_philo;

struct	s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_time;
	bool	is_end;
  pthread_mutex_t write;
	t_fork	*forks;
	t_philo	*philos;
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
void	*ft_malloc(size_t bytes);
long  gettime_ms(void);
void print_state(long timestamp, int id, const char *state, t_table *table);
void precise_sleep(long milisec);
bool  philo_died(t_table *table);

// *** init.c ***
void	data_init(t_table *table);

// *** parsing.c ***
void	parse_input(t_table *table, char *argv[]);

void	party(t_table *table);

void  clean(t_philo *philos);