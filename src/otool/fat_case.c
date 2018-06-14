#include "../../includes/nm.h"

/*
** handles the case of the fat headers
** (only for the big endian architecture)
*/

void go_fat_big(char *ptr)
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
	while (nfats)
	{
		ft_printf("\n%u\n", nfats);
		if (swap_uint32(arch->cputype) == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void *);
		nfats--;
	}
	ft_otool((void *)ptr + swap_uint32(offset), NULL);
}

/*
** handles the case of the fat headers
** (only for the little endian architecture)
*/

void go_fat_lil(char *ptr)
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
	nfats = fat->nfat_arch;
	arch = (void *)ptr + sizeof(fat);
	while (nfats)
	{
		ft_printf("\n%u\n", nfats);
		if (arch->cputype == CPU_TYPE_X86_64)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void *);
		nfats--;
	}
	ft_otool((void *)ptr + offset, NULL);
}
