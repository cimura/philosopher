#include "philo.h"

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->is_end = false;
	// table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
	// table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	table->start_time = gettime_ms();
	ft_mutex(&table->write, INIT);
	while (i < table->philo_nbr)
	{
		//　⚠　3重マトリョーシカ現象が起きてます！！！解決！！
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].last_mealtime = 0;
		table->philos[i].left_fork_id = table->philos[i].philo_id;
		table->philos[i].right_fork_id = (table->philos[i].philo_id) % table->philo_nbr + 1;

		ft_mutex(&table->forks[i], INIT);
		ft_mutex(&table->philos[i].monitor, INIT);
		i++;
	}
	// philo_init(table);
}
