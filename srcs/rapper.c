#include "philo.h"

// void	ft_thread(pthread_t *thread, int flag, void *func(void *))
// {
// 	int	thread_value;

// 	thread_value = -1;
// 	if (flag == CREATE)
// 		thread_value = pthread_create(thread, NULL, func, NULL);
// 	else if (flag == DESTROY)
// 		thread_value = pthread_join(thread, NULL);
// 	else
// 		error_exit("thread flag is not good");
// 	if (thread_value != 0)
// 		error_exit("The return value of thread func is bad...");
// }

void	ft_mutex(pthread_mutex_t *mutex, int flag)
{
	int	mutex_value;

	mutex_value = -1;
	// printf("in ft_mutex, flag == %d\n", flag);
	if (flag == INIT)
		mutex_value = pthread_mutex_init(mutex, NULL);
	else if (flag == DESTROY)
		mutex_value = pthread_mutex_destroy(mutex);
	else if (flag == LOCK)
		{mutex_value = pthread_mutex_lock(mutex);
			printf("flag is lock\n");
		}
	else if (flag == UNLOCK)
		{mutex_value = pthread_mutex_unlock(mutex);
			printf("flag is unlock\n");
		}
	else
		error_exit("mutex flag is not good");
	if (mutex_value != 0)
		error_exit("The return value of mutex func is bad...");
}

void	*ft_malloc(size_t bytes)
{
	void	*memory;

	memory = malloc(bytes);
	if (!memory)
		error_exit("Failed with malloc");
	return (memory);
}