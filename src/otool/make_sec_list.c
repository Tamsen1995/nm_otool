#include "../../includes/nm.h"

/*
** puts the sought after sections into a t_section_list
*/

void process_sects(struct load_command *lc, t_section_list **sec_list)
{
	struct segment_command *seg;
	struct section *sec;
	uint32_t i;

	i = 0;
	seg = (struct segment_command *)lc;
	sec = (struct section *)((char *)seg + sizeof(struct segment_command));
	while (i < seg->nsects)
	{
		add_sec(sec_list, sec, NULL);
		sec = (struct section *)((void *)sec + sizeof(struct section));
		i++;
	}
}

/*
** puts the sought after sections into a t_section_list
** handles only the 64 case
*/

void process_sects_64(struct load_command *lc, t_section_list **sec_list)
{
	struct segment_command_64 *seg;
	struct section_64 *sec;
	uint32_t i;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)((char *)seg + sizeof(struct segment_command_64));
	while (i < seg->nsects)
	{

		add_sec(sec_list, NULL, sec);
		sec = (struct section_64 *)((void *)sec + sizeof(struct section_64));
		i++;
	}
}

/*
** a funtion which will take the lc and then iterate over all the lcs in order to find
** the lc_segments
** once found , it passes the lc_segment into the appropiate function to get a list
*/

void find_lc_segments(struct load_command *lc, char *ptr, t_section_list **sec_list, T_BOOL is_64)
{
	uint32_t i;
	struct mach_header_64 *header_64;
	struct mach_header *header;

	i = 0;
	if (is_64)
		header_64 = (struct mach_header_64 *)ptr;
	else
		header = (struct mach_header *)ptr;
	while (is_64 && i < header_64->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			process_sects_64(lc, sec_list);
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
	while (!is_64 && i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			process_sects(lc, sec_list);
		lc += lc->cmdsize / sizeof(void *);
		i++;
	}
}

/*
** frees the section list after otool execution
*/

void free_sec_list(t_section_list *list)
{
	t_section_list *tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		if (tmp->next)
			free(tmp->next);
		tmp = tmp->prev;
	}
	free(tmp);
}

/*
** passes the file ptr into the appropiate function
** so that a section list can be made.
*/

void	make_sec_list(char *ptr, char *filename, T_BOOL is_64)
{
	struct load_command *lc;
	t_section_list *sec_list;

	sec_list = NULL;
	if (is_64)
		lc = (void *)ptr + sizeof(struct mach_header_64);
	else
		lc = (void *)ptr + sizeof(struct mach_header);
	find_lc_segments(lc, ptr, &sec_list, is_64);
	if (is_64)
		output_sections_64(ptr, sec_list, filename);
	else	
		output_sections_32(ptr, sec_list, filename);
	free_sec_list(sec_list);
}
