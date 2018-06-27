/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:43:05 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 13:43:07 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nm.h"

void		ft_nm(char *ptr)
{
	unsigned int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC)
		handle_32(ptr);
	else if (magic_number == MH_CIGAM)
		fatal("Logic to swap bytes(BIG ENDIAN)");
	else if (magic_number == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_number == MH_CIGAM_64)
		ft_printf("Logic to swap bytes. (Big endian)");
	else if (magic_number == FAT_CIGAM)
		handle_fat_big(ptr);
	else if (magic_number == FAT_MAGIC)
		handle_fat_lil(ptr);
	else
		ft_printf("The file was not recognized as a valid object file\n");
}
