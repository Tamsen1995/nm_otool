#include "../../../includes/nm.h"

void free_sec_list_nm(t_lsection *sec_list)
{

	t_section *tmp;

	tmp = sec_list->first;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		if (tmp->next && tmp->next->name)
		{
			free(tmp->next->name);
			free(tmp->next);
		}
		tmp = tmp->prev;
	}
	free(tmp->name);
	free(tmp);
}

void handle_32(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header *header;
	struct load_command *lc;
	struct symtab_command *sym;
	t_lsection *sec_list;

	header = (struct mach_header *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	sec_list = get_sections_32(ptr);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			process_symtab_32(sym, ptr, sec_list);
			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	free_sec_list_nm(sec_list);
}
