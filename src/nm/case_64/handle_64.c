/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:04:32 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 14:04:33 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/nm.h"

void			handle_64(char *ptr)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	t_lsection				*sec_list;

	header = (struct mach_header_64 *)ptr;
	i = 0;
	lc = (void *)ptr + sizeof(*header);
	sec_list = get_sections_64(ptr);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			process_symtab_64(sym, ptr, sec_list);
			break ;
		}
		i++;
		lc = (void *)lc + lc->cmdsize;
	}
	free_sec_list_nm(sec_list);
}
