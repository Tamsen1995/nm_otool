#include "../../../includes/nm.h"

void add_seg_64(struct load_command *lc, t_lsection *list)
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

t_lsection *get_sections_64(char *ptr)
{
	t_lsection *list;
	struct mach_header_64 *header;
	struct load_command *lc;
	unsigned int i;

	if (!(list = (t_lsection *)malloc(sizeof(t_lsection))))
		return (NULL);

	i = 0;
	list->first = NULL;
	list->last = NULL;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
			add_seg_64(lc, list);
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	return (list);
}
