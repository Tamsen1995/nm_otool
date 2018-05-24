#include "../../../includes/nm.h"

void handle_64(char *ptr)
{
	int ncmds;
	int i;
	struct mach_header_64 *header;
	struct load_command *lc;
	struct symtab_command *sym;
	t_lsection *sec_list;

	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	sec_list = get_sections_64(ptr);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			process_symtab_64(sym, ptr, sec_list);
			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
}
