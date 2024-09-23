#include "philo.h"

void  clean(t_philo *philos)
{
  ft_mutex(&philos->left_fork.fork, DESTROY);
  ft_mutex(&philos->right_fork.fork, DESTROY);
  ft_mutex(&philos->monitor, DESTROY);
}