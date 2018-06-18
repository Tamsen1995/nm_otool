#include "../includes/nm.h"

void handle_fat_lil(char *ptr)
{
	uint32_t i;
	uint32_t offset;
	struct fat_header *fat;
	struct fat_arch *arch;

	i = 0;
	fat = (void *)ptr;
	arch = (void *)ptr + sizeof(fat);
	while (i < fat->nfat_arch)
	{
		if (arch->cputype == CPU_TYPE_X86_64 \
			|| arch->cputype == CPU_TYPE_X86)
			offset = arch->offset;
		arch += sizeof(arch) / sizeof(void *);
		i++;
	}
	ft_nm(ptr + offset);
}

void handle_fat_big(char *ptr)
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
			offset = swap_uint32(arch->offset);
		arch += sizeof(arch) / sizeof(void *);
		i++;
	}
	ft_nm(ptr + offset);
}