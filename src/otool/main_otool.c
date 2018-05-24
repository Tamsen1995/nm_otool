#include "../../includes/nm.h"

void otool_64(char *ptr)
{
	t_lsection *sec_list;
	t_section *tmp; // TESTING

	sec_list = get_sections_64(ptr);
	tmp = sec_list->first;
	//////////////////////
	while (tmp)
	{
		ft_printf("\n%s\n", tmp->name);
		tmp = tmp->next;
	}



	////////////////




	exit(0); // TESTING



}

void ft_otool(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		otool_64(ptr);

}

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
	ft_otool(ptr); // This is where enter the main flow of the nm
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}