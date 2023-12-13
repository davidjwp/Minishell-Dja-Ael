#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write (2, "in sig_handler\n", 16);
		exit(EXIT_SUCCESS);
	}
}

int	child_pro(void)
{
	pid_t	child;
	int		stat;

	child = fork();
	if (child == -1)
		return (perror("fork fail"), 0);
	if (child)
		return (wait(&stat), 1);
	signal(SIGINT, sig_handler);
	write(2,"HERE\n",6);
	sleep (60);
	return (exit(EXIT_SUCCESS), 1);
}

int	main(void)
{
	pid_t	parent;
	int		stat;

	parent = fork();
	if (parent == -1)
		return (perror("fork fail"), 0);
	if (!parent)
		return (child_pro(), 0);
	child_pro();
	wait(&stat);
	return (1);
}
