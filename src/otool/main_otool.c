#include "../../includes/nm.h"

// #define FAT_MAGIC	0xcafebabe
// #define FAT_CIGAM	NXSwapLong(FAT_MAGIC)

// struct fat_header {
// 	unsigned long	magic;		/* FAT_MAGIC */
// 	unsigned long	nfat_arch;	/* number of structs that follow */
// };

// struct fat_arch {
// 	cpu_type_t	cputype;	/* cpu specifier (int) */
// 	cpu_subtype_t	cpusubtype;	/* machine specifier (int) */
// 	unsigned long	offset;		/* file offset to this object file */
// 	unsigned long	size;		/* size of this object file */
// 	unsigned long	align;		/* alignment as a power of 2 */
// };

/*
** handles the case of the fat headers
** (only for the big endian architecture)
*/

void go_fat(char *ptr)
{
	struct fat_header *fat;
	struct fat_arch *arch;
	uint32_t nfats;
	uint32_t offset;

	nfats = 0;
	offset = 0;
	if (!ptr)
		return;
	fat = (void *)ptr;
	nfats = swap_uint32(fat->nfat_arch);
	arch = (void *)ptr + sizeof(fat);
	// in order to get to the first fat archive
	// we need to jump a fat_header ahead of the pointer beg
	while (nfats)
	{
		// swap the bytes of the arch->cputype in order to
		// check which cpu type we're dealing with
		// if it's CPU_TYPE_X86_64 then the offset should be that archive
		// in order to read anything in the arch header
		ft_printf("\n%u\n", nfats);
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void *);
		nfats--;
	}

	// I will need to swap the bytes since everything in the
	// fat header is of little endian
	ft_otool((void *)ptr + swap_uint32(offset), "NULL");
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
		sec_list = make_sec_list(ptr, FALSE);
		output_sections_32(ptr, sec_list, filename);
	}
	else if (magic_number == FAT_CIGAM) // || magic_number == FAT_MAGIC)
	{
		go_fat(ptr);
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