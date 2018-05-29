#include "../../includes/nm.h"

void process_sects_64(struct load_command *lc)
{
	struct segment_command_64 *seg;
	struct section_64 *sec;
	uint32_t i;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)((char *)seg + sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{

		ft_putendl(sec->sectname);			   // TESTING
		ft_printf("\n%d\n", (int)sec->offset); // TESTING
		sec = (struct section_64 *)((void *)sec + sizeof(struct section_64));
		i++;
	}

	// so if I code this well I should be able to get out all the section names
}

/*
** a funtion which will take the lc and then iterate over all the lcs in order to find
** the lc_segments
** once found , it passes the lc_segment into the appropiate function to get a list
*/

void find_lc_segments(struct load_command *lc, char *ptr, T_BOOL is_64)
{
	struct mach_header_64 *header;

	if (is_64)
		header = (struct mach_header_64 *)ptr;
	else
		header = header = (struct mach_header *)ptr;

	// while (i < header->ncmds && is_64 == TRUE)
	// {
	// 	if (lc->cmd == LC_SEGMENT_64)
	// 		process_sects(lc);
	// 	lc += lc->cmdsize / sizeof(void *);
	// 	i++;
	// }

	// while (i < header->ncmds && is_64 == TRUE)
	// {
	// 	if (lc->cmd == LC_SEGMENT_64)
	// 		process_sects(lc);
	// 	lc += lc->cmdsize / sizeof(void *);
	// 	i++;
	// }

	// TODO : FINISH THIS FUNCTION
}

/*
** passes the file ptr into the appropiate function
** so that a section list can be made.
*/

t_section_list *make_sec_list(char *ptr, T_BOOL is_64)
{
	struct load_command *lc;
	t_section_list *sec_list;

	if (is_64)
		lc = (void *)ptr + sizeof(struct mach_header_64);
	else
		lc = (void *)ptr + sizeof(struct mach_header);
	find_lc_segments(lc, ptr, is_64);
	return (sec_list);

	exit(0); // TESTING
}

/*
** checking for the magic number
** and redirecting the flow into the proper
** case
*/

void ft_otool(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		make_sec_list(ptr, TRUE);
	else if (magic_number == MH_MAGIC)
		make_sec_list(ptr, FALSE);
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
	ft_otool(ptr); // This is where enter the main flow of the nm
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}