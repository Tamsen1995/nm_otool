/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 20:45:11 by tbui              #+#    #+#             */
/*   Updated: 2015/11/25 20:46:32 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void		my_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putendl_fd(char const *str, int fd)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		my_putchar_fd(str[i], fd);
		i++;
	}
	my_putchar_fd('\n', fd);
}
