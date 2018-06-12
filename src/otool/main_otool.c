#include "../../includes/nm.h"

/*
** a utility to reverse a string
** it allocates a new string which will be
** the reverse of the given string
** TODO : Put into libft
*/

char *reverse_string(char *str)
{
	int i;
	int str_len;
	char *ret;

	i = 0;
	ret = NULL;
	str_len = ft_strlen(str) - 1;
	if (!str)
		return (NULL);
	ret = ft_strnew(ft_strlen(str));
	while (str[i] && str_len > -1)
	{
		ret[i] = str[str_len];
		str_len--;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static char read_tab(int i)
{
	char *tab;

	tab = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (tab[i]);
}

char *ft_itoa_base(int num, int base)
{
	int i;
	unsigned int unsigned_val;
	char *str;
	char *ret;

	i = 0;
	str = ft_strnew(50);
	ret = NULL;
	unsigned_val = (unsigned int)num;
	while (unsigned_val > 0)
	{
		str[i] = read_tab(unsigned_val % base);
		unsigned_val = unsigned_val / base;
		i++;
	}
	str[i] = '\0';
	ret = reverse_string(str);
	free(str);
	return (ret);
}

/*
** prints out the text instructions of the
** section pointer
*/

void print_sec_info(uint64_t addr, uint64_t size, char *sec_ptr)
{
	uint64_t i;

	i = 0;
	if (!sec_ptr)
		fatal("Error in print_sec_info()");
	while (i < size)
	{
		//	if (i % 16 != 0)
		ft_printf("-> %s ", ft_itoa_base(sec_ptr[i], 16));
		i++;
	}


	// TODO : Finish this function
	// make sure to iterate the "size" through the sec_ptr[i]
	// and print out all the pointer indexes in base 16 with itoa base
	// every sixteenth position shall be an address

	ft_printf("\n%ap --- %u\n", addr, size); // TESTING
}

/*
** a function outputting all the necessary info
** of the sections needed by the otool
*/

void output_sections_64(char *ptr, t_section_list *sec_list)
{
	t_section_list *tmp;

	tmp = sec_list;
	while (tmp)
	{

		if (!ft_strcmp(tmp->section_64->sectname, TUT) && !ft_strcmp(tmp->section_64->segname, TXT))
		{
			// only if they're text sections within text segments to we want to print them.
			print_sec_info(tmp->section_64->addr, tmp->section_64->size, ptr + tmp->section_64->offset);
		}

		tmp = tmp->next;
	}
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
		output_sections_64(ptr, sec_list);
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