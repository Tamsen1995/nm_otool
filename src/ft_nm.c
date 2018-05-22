#include "../includes/nm.h"


void handle_fat(char *ptr)
{
	struct fat_header *fat;
	uint32_t num_of_structs;


	fat = (void *)ptr;
	num_of_structs = swap_uint32(num_of_structs);

	


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
