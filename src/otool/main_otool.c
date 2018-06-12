#include "../../includes/nm.h"

/*
** prints out the text instructions of the
** section pointer
*/

void print_sec_info(uint64_t addr, uint64_t size, char *sec_ptr)
{
	uint64_t i;
	char *str;

	i = 0;
	str = NULL;
	if (!sec_ptr)
		fatal("Error in print_sec_info()");
	while (i < size)
	{
		str = ft_itoa_base(sec_ptr[i], 16);
		str = adjust_str(str, 2);
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%ap\t", addr);
		}
		ft_printf("%s ", str);
		if ((i + 1) % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
}

/*
** a function outputting all the necessary info
** of the sections needed by the otool
*/

void output_sections_64(char *ptr, t_section_list *sec_list, char *filename)
{
	t_section_list *tmp;

	tmp = sec_list;
	while (tmp)
	{

		if (!ft_strcmp(tmp->section_64->sectname, TUT) && !ft_strcmp(tmp->section_64->segname, TXT))
		{
			ft_printf("\n%s:\n", filename);
			ft_printf("Contents of (__TEXT,__text) section\n");
			print_sec_info(tmp->section_64->addr, tmp->section_64->size, ptr + tmp->section_64->offset);
		}
		tmp = tmp->next;
	}
	ft_printf("\n");
}

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
		ft_printf("Inside the MH_MAGIC 32 bit case"); // TESTING
		sec_list = make_sec_list(ptr, FALSE);
	}
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