#include "../includes/nm.h"

t_symbols *bubble_sort(t_symbols *sym_list)
{
	t_symbols *tmp;

	tmp = sym_list;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if ((tmp && tmp->prev) && ft_strcmp(tmp->name, tmp->prev->name) < 0) // TESTING
		{
			
			// exchange the tmp and tmp->prev
		}
		tmp = tmp->next;
	}
	return (sym_list);
}