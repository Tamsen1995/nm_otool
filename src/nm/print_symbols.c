#include "../../includes/nm.h"

void print_symbols(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	if (!tmp)
		fatal("No symbols found in (print_symbols)");
	while (tmp)
	{
		if (tmp->value != 0)
			ft_printf("%ap ", tmp->value);
		else
			ft_putstr("\t\t ");
		ft_printf("%c %s\n", tmp->type, tmp->name);
		tmp = tmp->next;
	}

}