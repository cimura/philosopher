/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 18:55:17 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean(t_table *table)
{
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
			return (EXIT_FAILURE);
		if (join_threads(&table) == JOIN_ERR)
			return (1);
		clean(&table);
	}
	else
		print_error("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
