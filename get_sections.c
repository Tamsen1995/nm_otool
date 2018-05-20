#include "./includes/nm.h"

/*
** Will add a section element to the end of the section list
** This list is used to determine the type of an element
** of the type N_SECT
*/

void		add_to_list(char *sectname, t_lsection *list)
{
	ft_putendl(sectname); // TESTING
	list = NULL;
}

void		add_seg(struct load_command *lc, t_lsection *list)
{
	unsigned int i;
	struct segment_command_64 *seg;
	struct section_64 *sec;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	while (i < seg->nsects)
	{
		add_to_list(sec->sectname, list);
		sec = (struct section_64 *)((void *)sec + sizeof(struct section_64));
		i++;
	}
}

t_lsection *get_sections(char *ptr)
{
	t_lsection *list;
	struct mach_header_64 *header;
	struct load_command *lc;
	unsigned int i;

	i = 0;
	list = NULL;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i < header->ncmds)
	{
		i++;

		if (lc->cmd == LC_SEGMENT_64)
		{
			add_seg(lc, list);
			//ft_putendl("Segment has been found."); // TESTING
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (list);
}
