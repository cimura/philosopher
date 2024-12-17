#include <unistd.h>
#include <stdio.h>

int	main() {
	pid_t	pid;
	printf("before fork: %d\n", pid);
	pid = fork();
	if (pid == 0)
		printf("after fork: %d\n", pid);
	else	
		printf("after fork: %d\n", pid);


}
