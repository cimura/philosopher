/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 11:45:32 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void	clean(t_table *table)
{
	exit(0);
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->write_lock);
}
