/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:07:44 by sshimura          #+#    #+#             */
/*   Updated: 2024/12/20 11:35:33 by cimy             ###   ########.fr       */
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

	//printf("lock\n");
	//sem_wait(table->write_lock);
	timestamp = gettime_ms() - table->start_time;
	//sem_post(table->write_lock);
	printf("%lld %d %s\n", timestamp, id, state);
	//printf("unlock\n");
}

//char	*ft_itoa(int num)
//{
	
//}



// void	ft_mutex(pthread_mutex_t *mutex, int flag)
// {
// 	int	mutex_value;

// 	mutex_value = -1;
// 	if (flag == INIT)
// 		mutex_value = pthread_mutex_init(mutex, NULL);
// 	else if (flag == DESTROY)
// 		mutex_value = pthread_mutex_destroy(mutex);
// 	else if (flag == LOCK)
// 		mutex_value = pthread_mutex_lock(mutex);
// 	else if (flag == UNLOCK)
// 		mutex_value = pthread_mutex_unlock(mutex);
// 	if (mutex_value != 0)
// 		print_error("The return value of mutex func is bad...");
// }
