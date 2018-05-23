#include "../includes/nm.h"

/*
** gets rid of all duplicate symbol values as well as the stab values
** (symbols of type z)
*/

t_symbols *del_dupl_nd_stabs(t_symbols *sym_list)
{
	t_symbols *tmp;
	t_symbols *tmp2;

	tmp = sym_list;
	while (tmp)
	{
		if ((tmp->type == 'z' || tmp->type == 'Z') ||
			(tmp->next && tmp->value && tmp->value == tmp->next->value))
		{
			if (tmp->type != 'z' && tmp->type != 'Z' && tmp->type == '?')
				tmp = tmp->next;
			// tmp at THIS point should be the item to be deleted.
			tmp2 = tmp->next;
			if (tmp2)
				tmp2->prev = tmp->prev;
			if (tmp->prev)
				tmp->prev->next = tmp2;
			else
				sym_list = tmp2;
			free(tmp);
			free(tmp->name);
		}
		tmp = tmp->next;
	}
	return (sym_list);
}

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
	sym_list = del_dupl_nd_stabs(sym_list);
	sym_list = bubble_sort(sym_list);
	print_symbols(sym_list);
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
			sym = (struct symtab_command *)lc;
			process_symtab(sym, ptr, sec_list);
			break;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
}
