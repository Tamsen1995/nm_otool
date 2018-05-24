#include "../../../includes/nm.h"

void add_seg_32(struct load_command *lc, t_lsection *list)
{
	unsigned int i;
	struct segment_command *seg;
	struct section *sec;

	i = 0;
	seg = (struct segment_command *)lc;
	sec = (struct section *)(seg + sizeof(seg) / sizeof(void *));
	while (i < seg->nsects)
	{
		add_to_list(sec->sectname, list);
		sec = (struct section *)((void *)sec + sizeof(struct section));
		i++;
	}
}

t_lsection *get_sections_32(char *ptr)
{
	t_lsection *list;
	struct mach_header *header;
	struct load_command *lc;
	unsigned int i;

	if (!(list = (t_lsection *)malloc(sizeof(t_lsection))))
		return (NULL);

	i = 0;
	list->first = NULL;
	list->last = NULL;
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			add_seg_32(lc, list);
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	return (list);
}
