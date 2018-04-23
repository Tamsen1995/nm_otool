#include "./includes/nm.h"

void print_output(int nsyms, int symoff, int stroff, char *ptr)
{
	int i;
	char *stringtable;
	struct nlist_64 *array;

	// symbol table
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	for (i = 0; i < nsyms; ++i)
	{
		printf("->  %s\n", stringtable + array[i].n_type);
		printf("--->  %s\n", stringtable + array[i].n_un.n_strx);
	}
}

void handle_64(char *ptr)
{
	int ncmds; //  number of commands
	int i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;

	// declaring the head of the pointer as
	// a mach-o header structure
	header = (struct mach_header_64 *)ptr;
	// the header has the number of commands as a property
	ncmds = header->ncmds;
	i = 0;
	// putting the lc ptr the load commands
	lc = (void *)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			// if there is a symtab command
			// point the sym pointer to it.
			sym = (struct symtab_command *)lc;
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
}

void nm(char *ptr)
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
** Map file into memroy
** Display header
*/

int main(int ac, char **av)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (ac != 2)
	{
		fprintf(stderr, "Please give me an argument !\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr); // This is where enter the main flow of the nm
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}