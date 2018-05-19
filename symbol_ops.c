#include "./includes/nm.h"

t_symbols *new_symbol(char *strtable, struct nlist_64 list, t_lsection *sec_list)
{
	t_symbols *new;

	new = NULL;
	if (!(new = (t_symbols *)malloc(sizeof(t_symbols))))
		return (NULL);

	new->value = list.n_value;
	new->name = ft_strdup(strtable + list.n_un.n_strx);
	new->next = NULL;
	new->prev = NULL;

	// TODO : Implement a function which will determine
	// the type of the symbol
	//new->type = sym_type();
	// symbol type
	sec_list = NULL; // TESTING




	return (new);
}

void add_symbols(char *strtable,
				 struct nlist_64 list,
				 t_lsection *sec_list, t_symbols **sym_list)
{
	t_symbols *tmp;
	t_symbols *add;

	tmp = (*sym_list);
	add = new_symbol(strtable, list, sec_list);
	if (!tmp)
	{
		(*sym_list) = add;
	}
	else
	{
		tmp = (*sym_list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
}