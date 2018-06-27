/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_symtab_64.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:09:22 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 14:09:27 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/nm.h"

void		process_symtab_64(struct symtab_command \
*sym, char *ptr, t_lsection *sec_list)
{
	int					i;
	char				*strtable;
	struct nlist_64		*list;
	t_symbols			*sym_list;

	i = 0;
	sym_list = NULL;
	list = (void *)ptr + sym->symoff;
	strtable = (void *)ptr + sym->stroff;
	while (i < (int)sym->nsyms)
	{
		if (ft_strncmp(strtable + \
			list[i].n_un.n_strx, "/", 1) != 0 && \
			strtable + list[i].n_un.n_strx &&
			ft_strlen(strtable + list[i].n_un.n_strx) && \
			list[i].n_type != 100)
			add_symbols_64(strtable, list[i], \
			sec_list, &sym_list);
		i++;
	}
	sym_list = del_dupl_nd_stabs(sym_list);
	sym_list = bubble_sort(sym_list);
	print_symbols(sym_list, TRUE);
}
