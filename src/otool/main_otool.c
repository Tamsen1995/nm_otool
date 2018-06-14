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
	if (magic_number == MH_MAGIC_64)
	{
		sec_list = make_sec_list(ptr, TRUE);
		output_sections_64(ptr, sec_list, filename);
	}
	else if (magic_number == MH_MAGIC)
	{
		sec_list = make_sec_list(ptr, FALSE);
		output_sections_32(ptr, sec_list, filename);
	}
	else if (magic_number == FAT_CIGAM) // || magic_number == FAT_MAGIC)
		go_fat_big(ptr);
	else if (magic_number == FAT_MAGIC)
		go_fat_lil(ptr);
	else if (ft_strncmp(ptr, ARMAG, SARMAG) == 0)
		go_archive(ptr, filename);
}

/*
** opens the file and scans it into memory
** then passes it on into the otool flow
*/

int main(int ac, char **av)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (ac != 2)
		fatal("Please give me an argument !\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		fatal("open");
	if (fd != -1 && (fstat(fd, &buf) == -1))
		fatal("fstat in the main");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		fatal("mmap");
	ft_otool(ptr, av[1]);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}