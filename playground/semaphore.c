#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

sem_t *sem;  // セマフォのポインタ

// セマフォを使って共有リソースにアクセス
void use_resource(int id) {
	sem_wait(sem);
	sem_wait(sem);
	printf("Process %d: Using the resource!\n", id);
	sleep(1);
	printf("Process %d: Done using the resource!\n", id);
	sem_post(sem);
	sem_post(sem);
	exit(0);
}

int main() {
	pid_t	pid[3];
	sem = sem_open("/no", O_CREAT, 0644, 3);

	for (int i = 0; i < 3; ++i)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i % 2 == 0)
				usleep(10000);
			use_resource(i);
		}
	}
	for (int j = 0; j < 3; ++j)
		waitpid(pid[j], NULL, 0);
	sem_unlink("/no");
	return 0;
}
