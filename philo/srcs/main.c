/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/07 19:03:44 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_table *table)
{
	int	i;

	ft_mutex(&table->write, DESTROY);
	ft_mutex(&table->_end.lock, DESTROY);
	i = 0;
	while (i < table->philo_nbr)
	{
		ft_mutex(&table->forks[i + 1], DESTROY);
		ft_mutex(&table->philos[i]._meal.lock, DESTROY);
		ft_mutex(&table->philos[i]._time.lock, DESTROY);
		i++;
	}
	free(table->philos);
	free(table->forks);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse_input(&table, argv) == PARSE_ERR)
			return (EXIT_FAILURE);
		if (data_init(&table) == 1)
			return (EXIT_FAILURE);
		if (create_threads(&table) == THREAD_ERR)
			return (clean(&table), EXIT_FAILURE);
		if (join_threads(&table) == JOIN_ERR)
			return (clean(&table), 1);
		clean(&table);
	}
	else
		print_error("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
