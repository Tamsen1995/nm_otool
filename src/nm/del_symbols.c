#include "../../includes/nm.h"

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
