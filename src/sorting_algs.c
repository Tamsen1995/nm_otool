#include "../includes/nm.h"

T_BOOL not_sorted(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	while (tmp)
	{
		if ((tmp && tmp->prev) && ft_strcmp(tmp->name, tmp->prev->name) < 0)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

t_symbols *bubble_sort(t_symbols *sym_list)
{
	t_symbols *tmp;
	t_symbols *retainer;

	tmp = sym_list;
	retainer = NULL;
	if (!tmp)
		return (NULL);
	while (!not_sorted(sym_list))
	{
		tmp = sym_list;
		while (tmp)
		{
			if ((tmp && tmp->prev) && ft_strcmp(tmp->name, tmp->prev->name) < 0) // TESTING
			{
				retainer = tmp->prev;
				if (tmp->prev->prev)
					tmp->prev->prev->next = tmp;
				else
					sym_list = tmp;
				if (tmp->prev->prev)
					tmp->prev = tmp->prev->prev;
				else
					tmp->prev = NULL;
				retainer->next = tmp->next;
				tmp->next = retainer;
			}
			tmp = tmp->next;
		}
	}
	return (sym_list);
}