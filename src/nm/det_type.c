/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   det_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:38:45 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 13:38:47 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nm.h"

char		type_in_sects(t_lsection *sec_list, uint32_t n_sect)
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

char		determine_type(uint32_t type, \
uint32_t n_sect, t_lsection *sec_list, int addr)
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
