/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/10/09 21:13:51 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		parse_input(&table, argv);
		data_init(&table);
		create_philos(&table);
		join_threads(&table);
//    printf("philo_id is %d\n", table.philos->philo_id);
	}
	else
		error_exit("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
