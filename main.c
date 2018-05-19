#include "./includes/nm.h"

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *array;

	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		//	printf("->  %u\n", array[i].n_type);
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		++i;
	}
}

void	process_symtab(struct symtab_command *sym, char *ptr, t_lsection *sec_list)
{

	int i;
	char *strtable;
	struct nlist_64 *list;
	t_symbols *sym_list;

	i = 0;
	sec_list = NULL; // TESTING
	list = (void *)ptr + sym->symoff;
	sym_list = NULL;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		// TODO : Add the symbols into a list if the list[i].ntype does not equal to 100
			// if the string does not equal to "/"
			// and if the string is even present.

		i++;
	}

	exit(0); // TESTING

}

void	handle_64(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;
	t_lsection *sec_list;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	sec_list = get_sections(ptr);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			// TODO : Put all the symbols and their types into
			// a linked list

			// if there is a symtab command
			// point the sym pointer to it.
			sym = (struct symtab_command *)lc;
			// TODO: A function which will take the sym table and 
			// extract all the symbols' names as well as types
			process_symtab(sym, ptr, sec_list);
			
			
			//print_output(sym->nsyms, sym->symoff, sym->stroff, ptr); // subject to deletion
			
			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
}

void ft_nm(char *ptr)
{
	unsigned int magic_number;

	// the magic number is at the head of the mach-o header
	magic_number = *(int *)ptr;

	// the magic number indicates the architecture
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_CIGAM_64)
		printf("Logic to swap bytes. (Little endian)"); // TODO : Implement

	// TODO : Handle fat binaries
	// several architectures.
}

/*
** Contol flow:
** Read file
** Map file into memory
** Display header
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
	ft_nm(ptr); // This is where enter the main flow of the nm
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}