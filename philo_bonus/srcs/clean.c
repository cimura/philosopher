/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 12:46:07 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void	clean(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/write_lock");
	sem_close(table->forks);
	sem_close(table->death);
	sem_close(table->write_lock);
}
