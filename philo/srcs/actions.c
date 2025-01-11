/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/11 10:17:47 by cimy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	enque(t_table *table, int id)
{
	ft_mutex(&table->que.lock, LOCK);
	//if (table->que.head == (table->que.tail + 1) % table->philo_nbr)
	//{
	//	printf("que max\n");
	//	ft_mutex(&table->que.lock, UNLOCK);
	//	return ;
	//}
	table->que.memory[table->que.tail] = id;
	table->que.tail++;
	if (table->que.tail == table->philo_nbr)
		table->que.tail = 0;
	ft_mutex(&table->que.lock, UNLOCK);
}

int	deque(t_table *table, int id)
{
	ft_mutex(&table->que.lock, LOCK);
	//if (table->que.head == table->que.tail)
	//{
	//	printf("head == tail::: %d deq\n", id);
	//	ft_mutex(&table->que.lock, UNLOCK);
	//	return -1;
	//}
	int res = table->que.memory[table->que.head];
	if (res != id)
	{
		ft_mutex(&table->que.lock, UNLOCK);
		return -1;
	}
	table->que.head++;
	if (table->que.head == table->philo_nbr)
		table->que.head = 0; 
	ft_mutex(&table->que.lock, UNLOCK);
	return (res);
}

static void	tune_philo(t_philo *philos)
{
	while (!is_end(philos))
	{
		if (deque(philos->table, philos->philo_id) == philos->philo_id)
			break ;
		precise_sleep(philos, 5);
	}
	ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
	print_state(philos->philo_id,
			"has taken a fork", philos->table);
	ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
	print_state(philos->philo_id,
			"has taken a fork", philos->table);
	enque(philos->table, philos->philo_id);
}

void	taking_forks(t_philo *philos)
{
	if (philos->table->philo_nbr % 2 != 0)
		tune_philo(philos);
	else if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
		ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
		print_state(philos->philo_id,
			"has taken a fork", philos->table);
	}
}

void	eating(t_philo *philos)
{
	taking_forks(philos);
	print_state(philos->philo_id,
		"is eating", philos->table);
	precise_sleep(philos, philos->table->time_to_eat);
	ft_mutex(&philos->_meal.lock, LOCK);
	philos->_meal.meal_counter++;
	ft_mutex(&philos->_meal.lock, UNLOCK);
	ft_mutex(&philos->_time.lock, LOCK);
	philos->_time.last_mealtime = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->_time.lock, UNLOCK);
	if (philos->philo_id % 2 == 0)
	{
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
	}
	else
	{
		ft_mutex(&philos->table->forks[philos->right_fork_id], UNLOCK);
		ft_mutex(&philos->table->forks[philos->left_fork_id], UNLOCK);
	}
}

void	sleeping(t_philo *philos)
{
	print_state(philos->philo_id, "is sleeping", philos->table);
	precise_sleep(philos, philos->table->time_to_sleep);
}

void	thinking(t_philo *philos)
{
	print_state(philos->philo_id, "is thinking", philos->table);
}
