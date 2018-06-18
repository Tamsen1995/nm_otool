#include "../../../includes/nm.h"

void process_symtab_32(struct symtab_command *sym, char *ptr, t_lsection *sec_list)
{

	int i;
	char *strtable;
	struct nlist *list;
	t_symbols *sym_list;

	i = 0;
	sym_list = NULL;
	list = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + list[i].n_un.n_strx, "/", 1) != 0 && strtable + list[i].n_un.n_strx &&
			ft_strlen(strtable + list[i].n_un.n_strx) && list[i].n_type != 100)
			add_symbols_32(strtable, list[i], sec_list, &sym_list);
		i++;
	}
	sym_list = del_dupl_nd_stabs(sym_list);
	sym_list = bubble_sort(sym_list);
	print_symbols(sym_list, FALSE);
}
