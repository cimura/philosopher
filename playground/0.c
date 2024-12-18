#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void child(sem_t *sem) {
    printf("Child: Sleeping for 5 seconds...\n");
    usleep(5000000); // 5秒間スリープ
    printf("Child: Posting semaphore\n");
    sem_post(sem);
    exit(0); // 子プロセスを終了
}

int main() {
    sem_t *sem = sem_open("/no", O_CREAT, 0644, 0);

    pid_t pid = fork();
    if (pid == 0) {
        child(sem);
    } else {
        // 親プロセス
            printf("Parent: Waiting for semaphore...\n");
			sem_wait(sem);
			printf("hi\n");
        sem_unlink("/no");
        sem_close(sem);
        waitpid(pid, NULL, 0); // 子プロセスの終了を待つ
    }

    return 0;
}
