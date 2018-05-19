#include "./includes/nm.h"

void process_symtab(struct symtab_command *sym, char *ptr, t_lsection *sec_list)
{

	int i;
	char *strtable;
	struct nlist_64 *list;
	t_symbols *sym_list;

	i = 0;
	sym_list = NULL;
	list = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0 && strtable + list[i].n_un.n_strx &&
			ft_strlen(strtable + list[i].n_un.n_strx) && list[i].n_type != 100)
			add_symbols(strtable, list[i], sec_list, &sym_list);
		i++;
	}

	
	print_symbols(sym_list); // TESTING

	exit(0); // TESTING
}

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
	sec_list = get_sections(ptr);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			// TODO : Put all the symbols and their types into
			// a linked list

			// if there is a symtab command
			// point the sym pointer to it.
			sym = (struct symtab_command *)lc;
			// TODO: A function which will take the sym table and
			// extract all the symbols' names as well as types
			process_symtab(sym, ptr, sec_list);

			//print_output(sym->nsyms, sym->symoff, sym->stroff, ptr); // subject to deletion

			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
}
