#include "../../includes/nm.h"
void print_symbols(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	while (tmp)
	{
		ft_putchar(tmp->type);
		ft_putstr("\t");
		ft_putendl(tmp->name);
		tmp = tmp->next;
	}

}