/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:32 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 21:21:59 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_sem_meal_lock(t_table *table)
{
	int		i;
	char	*uniq_id;
	char	*name;

	i = 0;
	while (i < table->philo_nbr)
	{
		uniq_id = ft_itoa(table->philos[i].philo_id);
		if (uniq_id == NULL)
			return ;
		name = ft_strjoin("/sem_meal", uniq_id);
		if (name == NULL)
			return ;
		sem_close(table->philos[i].meal_lock);
		sem_unlink(name);
		free(name);
		free(uniq_id);
		i++;
	}
}

static void	clean(t_table *table)
{
	clean_sem_meal_lock(table);
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->write_lock);
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/write_lock");
	free(table->philos);
}

static int	wait_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (waitpid(table->philos[i].pid, NULL, 0) == -1)
			return (1);
		i++;
	}
	sem_post(table->death);
	pthread_join(table->death_waiter, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse_input(&table, argv) == PARSE_ERR)
			return (1);
		if (data_init(&table) == 1)
			return (1);
		if (create_philos(&table) == 1)
			return (1);
		if (wait_all_philos(&table) == 1)
			return (1);
		clean(&table);
	}
	else
		print_error("Wrong input:\n"
			GREEN"example// ./philo 5 800 200 200 [5]"RESET);
	return (0);
}
