/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/21 20:23:38 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	gettime_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_sleep(long long milisec)
{
	long long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < milisec)
		usleep(1000);
}

void	print_error(const char *message)
{
	printf(RED"%s\n"RESET, message);
}

void	print_state(int id, const char *state, t_table *table)
{
	long long	timestamp;

	sem_wait(table->write_lock);
	timestamp = gettime_ms() - table->start_time;
	sem_post(table->write_lock);
	printf("%lld %d %s\n", timestamp, id, state);
}
