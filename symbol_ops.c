#include "./includes/nm.h"

char type_in_sects(t_lsection *sec_list, uint32_t n_sect)
{
	//t_section *tmp;

	//tmp = sec_list->first;
	ft_putendl("Inside of type_in_sects"); // TESTING
	ft_putnbr((int)n_sect); // TESTING
	// while (tmp)
	// {
	// 	tmp = tmp->next;
	// }
	sec_list = NULL; // TESTING
	return ('S');
}

char determine_type(uint32_t type, uint32_t n_sect, t_lsection *sec_list, int addr)
{
	char ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'C';
		else
			ret = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'U';
	else if ((type & N_SECT) == N_SECT)
	{
		ret = 'S';
		type_in_sects(sec_list, n_sect);
	}
	else if ((type & N_TYPE) == N_INDR)
		ret = 'I';
	if ((type & N_STAB) != 0)
		ret = 'Z';
	if ((type & N_EXT) == 0 && ret != '?')
		ret += 32;
	return (ret);
}

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

	new->type = determine_type(list.n_type, list.n_sect, sec_list, list.n_value);

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