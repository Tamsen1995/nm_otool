/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_nm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:26:01 by tbui              #+#    #+#             */
/*   Updated: 2018/06/20 13:27:33 by tbui             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/nm.h"

/*
** prepares the file to be passed into the nm
** and then passes it into the nm
*/

static void		handle_file(char *filename)
{
	int			fd;
	struct stat	buf;
	char		*ptr;

	if ((fd = open(filename, O_RDONLY)) < 0)
		fatal("open");
	if (fd != -1 && (fstat(fd, &buf) == -1))
		fatal("fstat in the main");
	if ((ptr = mmap(0, buf.st_size, PROT_READ, \
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		fatal("mmap");
	ft_nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		fatal("munmap error in handle_file");
}

/*
** Flow:
** Read file
** Map file into memory
** Display symbol tables
*/

int				main(int ac, char **av)
{
	int			i;

	i = 1;
	if (ac < 2)
		fatal("Please give me an argument !\n");
	while (i < ac)
	{
		if (ac > 2)
			ft_printf("\n\n%s: \n", av[i]);
		handle_file(av[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
