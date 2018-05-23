#include "../../../includes/nm.h"

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
			add_seg(lc, list);
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	return (list);
}
