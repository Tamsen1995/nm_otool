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
		ft_putendl("One section"); // TESTING
		i++;
	}

	// so if I code this well I should be able to get out all the section names



}

void otool_64(char *ptr)
{
	uint32_t i;
	struct load_command *lc;
	struct mach_header_64 *header;

	i = 0;
	lc = (void *)ptr + sizeof(struct mach_header_64);
	header = (struct mach_header_64 *)ptr;
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			process_sects_64(lc);
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
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