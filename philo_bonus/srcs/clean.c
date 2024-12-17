/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:45:36 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/17 13:55:20 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"

void	clean(t_table *table)
{
	if (sem_close(table->sem) < 0)
		exit(EXIT_FAILURE);
	if (sem_unlink(table->sem_name) < 0)
		exit(EXIT_FAILURE);
}
