#include "../../includes/nm.h"

void print_symbols(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	while (tmp)
	{
		ft_printf("%ap %c %s\n", tmp->value, tmp->type, tmp->name);
		tmp = tmp->next;
	}

}