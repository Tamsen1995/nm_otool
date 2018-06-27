/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:41:01 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 13:41:03 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nm.h"

void		print_symbols(t_symbols *sym_list, T_BOOL is_64)
{
	t_symbols *tmp;

	tmp = sym_list;
	if (!tmp)
		fatal("No symbols found in (print_symbols)");
	while (tmp)
	{
		if (tmp->value != 0 && is_64)
			ft_printf("%ap ", tmp->value);
		else if (tmp->value != 0 && !is_64)
		{
			ft_printf("0000");
			ft_printf("%s ", printpointeur((void *)tmp->value, 1));
		}
		else if (is_64)
			ft_putstr("\t\t ");
		else
			ft_putstr("\t ");
		ft_printf("%c %s\n", tmp->type, tmp->name);
		tmp = tmp->next;
	}
}
