#include "./includes/nm.h"

void		add_seg(struct load_command *lc, t_lsection *list)
{
	unsigned int i;
	struct segment_command_64 *seg;
	struct section_64 *sec;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	list = NULL; // TESTING
//	ft_putnbr(seg->nsects); // TESTING
	while (i < seg->nsects)
	{
		// TODO : make a function which will add
			// sec->sectname's into the t_lsection *list
	//	ft_putendl(sec->sectname); // TESTING
		
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
