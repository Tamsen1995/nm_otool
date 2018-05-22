#include "../includes/nm.h"

char type_in_sects(t_lsection *sec_list, uint32_t n_sect)
{
	t_section *tmp;
	
	tmp = sec_list->first;
	while (tmp)
	{
		if (tmp->nb == n_sect)
		{
			if (!ft_strcmp(tmp->name, SECT_DATA))
				return ('D');
			else if (!ft_strcmp(tmp->name, SECT_BSS))
				return ('B');
			else if (!ft_strcmp(tmp->name, SECT_TEXT))
				return ('T');
			else
				return ('S');
		}
		tmp = tmp->next;
	}
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
		ret = type_in_sects(sec_list, n_sect);
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
	return (new);
}

/*
** creates new symbol
** determines its type
** puts it into the sym_list
** TODO : Sort the symbols according to the ascii table
*/
void add_symbols(char *strtable,
				 struct nlist_64 list,
				 t_lsection *sec_list, t_symbols **sym_list)
{
	t_symbols *tmp;
	t_symbols *add;
	t_symbols *ret;

	tmp = (*sym_list);
	ret = NULL;
	add = new_symbol(strtable, list, sec_list);
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