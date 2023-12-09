#include <stdio.h>
#include <sys/stat.h>

int	main(int ac, char **av)
{
	struct stat	dir;

	if (ac != 2)
		return (0);
	if (!stat(av[1], &dir))
		if (S_ISDIR(dir.st_mode))
			return (printf("%s: is a directory\n", av[1]), 0);
	printf("%s: is not a directory\n", av[1]);
	return (0);
}
