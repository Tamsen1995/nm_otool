#include "../../includes/nm.h"

/*
** checking for the magic number
** and redirecting the flow into the proper
** case
*/

void ft_otool(char *ptr, char *filename)
{
	unsigned int magic_number;
	t_section_list *sec_list;

	magic_number = *(int *)ptr;
	sec_list = NULL;

	if (magic_number == MH_CIGAM_64)
		fatal("This is the MH_CIGAM_64 Big endian case inside the ft_otool"); // TESTING
	if (magic_number == MH_MAGIC_64)
		make_sec_list(ptr, filename, TRUE);
	else if (magic_number == MH_MAGIC)
		make_sec_list(ptr, filename, FALSE);
	else if (magic_number == FAT_CIGAM)
		go_fat_big(ptr);
	else if (magic_number == FAT_MAGIC)
		go_fat_lil(ptr);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		go_archive(ptr, filename);
	else
	{
		ft_printf("%s:", filename);
		fatal(" is not an object file");
	}
}

/*
** opens the file and scans it into memory
** then passes it on into the otool flow
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
		if ((fd = open(av[i], O_RDONLY)) < 0)
			fatal("open");
		if (fd != -1 && (fstat(fd, &buf) == -1))
			fatal("fstat in the main");
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			fatal("mmap");
		ft_otool(ptr, av[i]);
		if (close(fd) == -1)
			fatal("close error");
		if (munmap(ptr, buf.st_size) < 0)
		{
			perror("munmap");
			return (EXIT_FAILURE);
		}
		i++;
	}

	return (EXIT_SUCCESS);
}