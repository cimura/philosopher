/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/08 21:04:45 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//static void	tune_philo(t_table *table, t_philo *philos)
//{
//	long long	since_lastmeal;
//	long long	eval;

//	eval = (philos->table->time_to_die
//			- (philos->table->time_to_eat + philos->table->time_to_sleep))
//		/ philos->table->philo_nbr;
//	sem_wait(philos->meal_lock);
//	since_lastmeal = gettime_ms() - table->start_time - philos->last_mealtime;
//	sem_post(philos->meal_lock);
//	if (eval < 10)
//		return ;
//	if (philos->last_mealtime > 0 && since_lastmeal < (table->time_to_die) / 2)
//		precise_sleep(1);
//}

int	taking_forks(t_table *table, t_philo *philos)
{
	sem_wait(table->forks.lock);
	sem_wait(table->forks.fork);
	print_state(philos->philo_id,
		"has taken a fork", table);
	sem_wait(table->forks.fork);
	print_state(philos->philo_id,
		"has taken a fork", table);
	sem_post(table->forks.lock);
	return (0);
}

int	eating(t_table *table, t_philo *philos)
{
	if (taking_forks(table, philos) == 1)
		return (1);
	print_state(philos->philo_id,
		"is eating", table);
	precise_sleep(philos->table->time_to_eat);
	sem_wait(philos->_meal.lock);
	philos->_meal.meal_counter++;
	sem_post(philos->_meal.lock);
	sem_wait(philos->_time.lock);
	philos->_time.last_mealtime = gettime_ms() - philos->table->start_time;
	sem_post(philos->_time.lock);
	sem_post(table->forks.fork);
	sem_post(table->forks.fork);
	return (0);
}

void	thinking(t_philo *philos)
{
	print_state(philos->philo_id, "is thinking", philos->table);
}

void	sleeping(t_philo *philos)
{
	print_state(philos->philo_id, "is sleeping", philos->table);
	precise_sleep(philos->table->time_to_sleep);
}
