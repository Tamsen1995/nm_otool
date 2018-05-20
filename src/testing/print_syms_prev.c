#include "../../includes/nm.h"

void print_syms_prev(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		ft_putchar(tmp->type);
		ft_putstr("\t");
		ft_putendl(tmp->name);
		tmp = tmp->prev;
	}

}