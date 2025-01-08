#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT and O_EXCL

typedef struct s_data {
    sem_t *sem;
} t_data;

void *philosopher_watcher(void *arg) {
    t_data *data = (t_data *)arg;
    sleep(2); // Simulate detecting death
    printf("Philosopher died. Notifying parent(in child thread).\n");
    sem_post(data->sem); // Notify parent
    return NULL;
}

int main() {
    sem_t *sem = sem_open("/philosopher", O_CREAT | O_EXCL, 0644, 0);
    
    pid_t pid = fork();
    if (pid < 0)
	    exit(1);
    else if (pid == 0)
    { // Child process
        pthread_t thread;
        t_data data = {sem};
        pthread_create(&thread, NULL, philosopher_watcher, &data);
        pthread_join(thread, NULL);
        sem_close(sem); // Close the semaphore in the child process
        exit(0);
    }
    else
    { // Parent process
		    printf("Waiting... (in parent process).\n");
        sem_wait(sem); // Wait for the child process to notify
	printf("Closing semphore...(in parent process).\n");
        sem_close(sem); // Close the semaphore in the parent process
        sem_unlink("/philosopher"); // Unlink the semaphore
    }
	printf("\tdone\n");
    return 0;
}
