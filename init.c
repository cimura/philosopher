#include "philo.h"

void	data_init(t_table table)
{
	int	i;

	i = 0;
	table.is_end = false;
	table.philos = ft_malloc(sizeof(t_philo) * table.philo_nbr);
	table.forks = ft_malloc(sizeof(t_fork) * table.philo_nbr);
  table.start_time = gettime_ms();
	while (i < table.philo_nbr)
	{
		table.forks[i].fork_id = i;
		ft_mutex(&table.forks[i].fork, INIT);
		ft_mutex(&table.philos[i].monitor, INIT);
		i++;
	}
	// philo_init(table);
}
