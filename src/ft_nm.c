#include "../includes/nm.h"


void handle_fat(char *ptr)
{
	uint32_t i;
	uint32_t offset;
	struct fat_header *fat;
	struct fat_arch *arch;

	i = 0;
	fat = (void *)ptr;
	arch = (void *)ptr + sizeof(fat);
	while (i < swap_uint32(fat->nfat_arch))
	{
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64 \
			|| swap_uint32(arch->cputype) == CPU_TYPE_X86)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void *);
		i++;
	}

	printf("\nthe offset is : %u\n", swap_uint32(offset)); // TESTING

	//CPU_TYPE_X86_64
	//CPU_TYPE_X86
	// These are the cpu types we're looking for.

	exit (0); // TESTING
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
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		handle_fat(ptr);


	// TODO : Handle fat binaries
	// several architectures.
}
