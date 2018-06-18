#include "../../includes/nm.h"

/*
** Flow:
** Read file
** Map file into memory
** Display symbol tables
*/

int main(int ac, char **av)
{
	int i;
	int fd;
	char *ptr;
	struct stat buf;

	i = 1;
	while (i < ac)
	{
		if (ac > 2)
			ft_printf("\n\n%s: \n", av[i]);
		if (ac < 2)
			fatal("Please give me an argument !\n");
		if ((fd = open(av[i], O_RDONLY)) < 0)
			fatal("open");
		if (fd != -1 && (fstat(fd, &buf) == -1))
			fatal("fstat in the main");
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			fatal("mmap");
		ft_nm(ptr); // This is where enter the main flow of the nm
		if (munmap(ptr, buf.st_size) < 0)
		{
			perror("munmap");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}