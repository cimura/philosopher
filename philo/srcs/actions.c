/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshimura <sshimura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:28:48 by sshimura          #+#    #+#             */
/*   Updated: 2025/01/10 20:36:06 by sshimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_que(t_table *table)
{
    int i;
    int head = table->que.head;
    int tail = table->que.tail;

    // キューが空の場合
    if (head == tail)
    {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue content: ");
    if (head < tail) 
    {
        // head から tail まで順に表示
        for (i = head; i < tail; i++)
        {
            printf("%d ", table->que.que[i]);
        }
    }
    else
    {
        // キューが循環している場合、head から末尾まで表示し、次に先頭から tail まで表示
        for (i = head; i < 201; i++)
        {
            printf("%d ", table->que.que[i]);
        }
        for (i = 0; i < tail; i++)
        {
            printf("%d ", table->que.que[i]);
        }
    }
    printf("\n");
}

void	enque(t_table *table, int id)
{
	// printf("enque: %d\n", id);
	ft_mutex(&table->que.lock, LOCK);
	if (table->que.head == (table->que.tail + 1) % 201)
	{
		printf("que max\n");
		return ;
	}
	table->que.que[table->que.tail++] = id;
	if (table->que.tail == 201)
		table->que.tail = 0;
	ft_mutex(&table->que.lock, UNLOCK);
	print_que(table);
}

int	deque(t_table *table, int id)
{
	// printf("deque: %d\n", id);
	ft_mutex(&table->que.lock, LOCK);
	if (table->que.head == table->que.tail)
	{
		// printf("que empty\n");
		ft_mutex(&table->que.lock, UNLOCK);
		return -1;
	}
	int res = table->que.que[table->que.head];
	if (res != id)
	{
		// printf("You are not Head(%d)\n", id);
		ft_mutex(&table->que.lock, UNLOCK);
		return -1;
	}
	// printf("Head\n");
	table->que.head++;
	if (table->que.head == 201)
		table->que.head = 0; 
	ft_mutex(&table->que.lock, UNLOCK);
	return (res);
}
//&& philos->table->forks[philos->left_fork_id].clean && philos->table->forks[philos->right_fork_id].clean

static void	tune_philo(t_philo *philos)
{
	while (1)
	{
		if (deque(philos->table, philos->philo_id) == philos->philo_id
		&& philos->table->forks[philos->left_fork_id].clean && philos->table->forks[philos->right_fork_id].clean)
		{
			philos->table->forks[philos->left_fork_id].clean = false;
			philos->table->forks[philos->right_fork_id].clean = false;
			printf("\t[%d] break\n", philos->philo_id);
			enque(philos->table, philos->philo_id);
			break;
		}
		// printf("i am %d, deq:result  %d\n", philos->philo_id, deque(philos->table, philos->philo_id));
		precise_sleep(philos, 50);
	}
	ft_mutex(&philos->table->forks[philos->right_fork_id].lock, LOCK);
	print_state(philos->philo_id,
			"has taken a fork", philos->table);
	ft_mutex(&philos->table->forks[philos->left_fork_id].lock, LOCK);
	print_state(philos->philo_id,
			"has taken a fork", philos->table);
	// ft_mutex(&philos->table->_hunger.lock, LOCK);
	// if (philos->philo_id != philos->table->_hunger.hungry_id
	// 	&& philos->_time.last_mealtime != 0)
	// {
	// 	precise_sleep(philos, philos->table->time_to_eat - (philos->table->time_to_sleep)/2 + 5);
	// }
	// ft_mutex(&philos->table->_hunger.lock, UNLOCK);
}

void	taking_forks(t_philo *philos)
{
	tune_philo(philos);
	// if (philos->philo_id % 2 == 0)
	// {
	// 	ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
	// 	print_state(philos->philo_id,
	// 		"has taken a fork", philos->table);
	// 	ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
	// 	print_state(philos->philo_id,
	// 		"has taken a fork", philos->table);
	// }
	// else
	// {
	// 	ft_mutex(&philos->table->forks[philos->left_fork_id], LOCK);
	// 	print_state(philos->philo_id,
	// 		"has taken a fork", philos->table);
	// 	ft_mutex(&philos->table->forks[philos->right_fork_id], LOCK);
	// 	print_state(philos->philo_id,
	// 		"has taken a fork", philos->table);
	// }
}

void	eating(t_philo *philos)
{
	taking_forks(philos);
	print_state(philos->philo_id,
		"is eating", philos->table);
	// enque
	// enque(philos->table, philos->philo_id);
	precise_sleep(philos, philos->table->time_to_eat);
	ft_mutex(&philos->table->forks->lock, LOCK);
	philos->table->forks[philos->left_fork_id].clean = true;
	philos->table->forks[philos->right_fork_id].clean = true;
	ft_mutex(&philos->table->forks->lock, UNLOCK);

	ft_mutex(&philos->_meal.lock, LOCK);
	philos->_meal.meal_counter++;
	ft_mutex(&philos->_meal.lock, UNLOCK);
	ft_mutex(&philos->_time.lock, LOCK);
	philos->_time.last_mealtime = gettime_ms() - philos->table->start_time;
	ft_mutex(&philos->_time.lock, UNLOCK);
	// if (philos->philo_id % 2 == 0)
	// {
		ft_mutex(&philos->table->forks[philos->left_fork_id].lock, UNLOCK);
		ft_mutex(&philos->table->forks[philos->right_fork_id].lock, UNLOCK);
	// }
	// else
	// {
	// 	ft_mutex(&philos->table->forks[philos->right_fork_id].lock, UNLOCK);
	// 	ft_mutex(&philos->table->forks[philos->left_fork_id].lock, UNLOCK);
	// }
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
