#include "../../includes/nm.h"

void ft_nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_CIGAM_64)
		ft_printf("Logic to swap bytes. (Little endian)"); // TODO : Implement
	else if (magic_number == FAT_CIGAM)
		handle_fat_big(ptr);
	else if (magic_number == FAT_MAGIC)
		handle_fat_lil(ptr);
}
