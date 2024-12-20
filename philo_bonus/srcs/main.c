/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 12:45:58 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse_input(&table, argv) == 1)
			return (1);
		if (data_init(&table) == 1)
			return (1);
		//if (create_death_waiter(&table) == 1)
		//	return (1);
		if (wait_all_philos(&table) == 1)
			return (1);
		clean(&table);
	}
	else
		print_error("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
