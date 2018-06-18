#include "../../../includes/nm.h"


t_symbols *new_symbol_32(char *strtable, struct nlist list, t_lsection *sec_list)
{
	t_symbols *new;

	new = NULL;
	if (!(new = (t_symbols *)malloc(sizeof(t_symbols))))
		return (NULL);
	new->value = list.n_value;
	new->name = ft_strdup(strtable + list.n_un.n_strx);
	new->next = NULL;
	new->prev = NULL;
	new->type = determine_type(list.n_type, list.n_sect, sec_list, list.n_value);
	return (new);
}

/*
** creates new symbol
** determines its type
** puts it into the sym_list
** TODO : Sort the symbols according to the ascii table
*/
void add_symbols_32(char *strtable,
				 struct nlist list,
				 t_lsection *sec_list, t_symbols **sym_list)
{
	t_symbols *tmp;
	t_symbols *add;
	t_symbols *ret;

	tmp = (*sym_list);
	ret = NULL;
	add = new_symbol_32(strtable, list, sec_list);
	if (!(*sym_list))
		(*sym_list) = add;
	else
	{
		while (tmp->next)
		{
			if (ft_strcmp(tmp->name, add->name) > 0)
			{
				ret = add_before(tmp, add);
				if (ret)
					(*sym_list) = ret;
				return ;
			}
			tmp = tmp->next;
		}
		if (!tmp->next)
		{
			tmp->next = add;
			tmp->next->prev = tmp;
		}
	}
}