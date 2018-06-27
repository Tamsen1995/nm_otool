/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_symbols_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:47:18 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 13:47:20 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/nm.h"

t_symbols	*new_symbol_64(char *strtable, \
struct nlist_64 list, t_lsection *sec_list)
{
	t_symbols *new;

	new = NULL;
	if (!(new = (t_symbols *)malloc(sizeof(t_symbols))))
		return (NULL);
	new->value = list.n_value;
	new->name = ft_strdup(strtable + list.n_un.n_strx);
	new->next = NULL;
	new->prev = NULL;
	new->type = determine_type(list.n_type, \
								list.n_sect, sec_list, list.n_value);
	return (new);
}

/*
** Adds a symbol element into the list
*/

void		add_into_sym_list(t_symbols *tmp, t_symbols *ret, \
t_symbols **sym_list, t_symbols *add)
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

/*
** creates new symbol
** determines its type
** puts it into the sym_list
*/

void		add_symbols_64(char *strtable,
				struct nlist_64 list,
				t_lsection *sec_list, t_symbols **sym_list)
{
	t_symbols *tmp;
	t_symbols *add;
	t_symbols *ret;

	tmp = (*sym_list);
	ret = NULL;
	add = new_symbol_64(strtable, list, sec_list);
	if (!(*sym_list))
		(*sym_list) = add;
	else
	{
		add_into_sym_list(tmp, ret, sym_list, add);
	}
}
