#include "../../includes/nm.h"

/*
** prints out the text instructions of the
** section pointer
*/

void print_sec_info(uint64_t addr, uint64_t size, char *sec_ptr, T_BOOL is_64)
{
	uint64_t i;
	char *str;

	i = 0;
	str = NULL;
	if (!sec_ptr)
		fatal("Error in print_sec_info()");
	while (i < size)
	{
		str = ft_itoa_base(sec_ptr[i], 16);
		str = adjust_str(str, 2);
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			if (is_64)
				ft_printf("%ap\t", addr);
			else
			{
				ft_printf("0000");
				ft_printf("%s\t", printpointeur((void *)addr, 1));
			}
		}
		ft_printf("%s ", str);
		if ((i + 1) % 16 == 0)
			write(1, "\n", 1);
		i++;
	}
}


/*
** a function outputting all the necessary info
** of the sections needed by the otool
*/

void output_sections_64(char *ptr, t_section_list *sec_list, char *filename)
{
	t_section_list *tmp;

	tmp = sec_list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->section_64->sectname, TUT) && !ft_strcmp(tmp->section_64->segname, TXT))
		{
			if (filename)
				ft_printf("\n%s:\n", filename);
			ft_printf("Contents of (__TEXT,__text) section\n");
			print_sec_info(tmp->section_64->addr, tmp->section_64->size, ptr + tmp->section_64->offset, TRUE);
		}
		tmp = tmp->next;
	}
	ft_printf("\n");
}

/*
** a function outputting all the necessary info
** of the sections needed by the otool
*/

void output_sections_32(char *ptr, t_section_list *sec_list, char *filename)
{
	t_section_list *tmp;

	tmp = sec_list;
	while (tmp)
	{

		if (!ft_strcmp(tmp->section_32->sectname, TUT) && !ft_strcmp(tmp->section_32->segname, TXT))
		{
			if (filename)
				ft_printf("\n%s:\n", filename);
			ft_printf("Contents of (__TEXT,__text) section\n");
			print_sec_info(tmp->section_32->addr, tmp->section_32->size, ptr + tmp->section_32->offset, FALSE);
		}
		tmp = tmp->next;
	}
	ft_printf("\n");
}
