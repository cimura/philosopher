#include "philo.h"

void	take_fork(t_philo philos)
{
	ft_mutex(&philos.left_fork.fork, LOCK);
	print_state(philos.philo_id, "has taken a fork(left)", philos);
	ft_mutex(&philos.right_fork.fork, LOCK);
	print_state(philos.philo_id, "has taken a fork(right)", philos);
}
void	eat(t_philo philos)
{
	ft_mutex(&philos.monitor, LOCK);
	print_state(philos.philo_id, "is eating", philos);
	
}



void	dinner_start(t_table table)
{
}
