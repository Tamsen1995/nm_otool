#include "../../includes/nm.h"

/*
** looks for the size of the first special archive member
** this archive member holds file's name's size in the name itself
** the actual name is right after the struct
*/

int get_archive_size(char *name)
{
	int ret;
	char *size_in_arname;

	ret = 0;
	size_in_arname = ft_strchr(name, '/') + 1;
	ret = ft_atoi(size_in_arname);
	return (ret);
}

t_ran_offset *create_ran_offset(uint32_t offset, uint32_t strx)
{
	t_ran_offset *new;

	new = NULL;
	if (!(new = (t_ran_offset *)malloc(sizeof(t_ran_offset))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->offset = offset;
	new->strx = strx;
	return (new);
}

/*
** making the offset list for the ranlib
*/

void add_ran_offset(t_ran_offset **lst, uint32_t offset, uint32_t strx)
{
	t_ran_offset *tmp;
	t_ran_offset *new;

	tmp = (*lst);
	new = create_ran_offset(offset, strx);
	if (!(*lst))
	{
		(*lst) = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

//TODO : FINISH FUNCTION

void free_offset_lst(t_ran_offset *lst)
{
	t_ran_offset *tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp->prev)
	{
		if (tmp->next)
			free(tmp->next);
		tmp = tmp->prev;
	}
	free(tmp);
}

/*
** handles the archive case
** the ranlibe_size indicates the amount of ranlibs there are in the file archive.
*/

void go_archive(char *ptr, char *filename)
{
	struct ar_hdr *arch;
	struct ranlib *ran;
	int after_slash_size;
	char *ranlib_size;
	int ran_size;
	int i;
	t_ran_offset *lst;

	i = 0;
	lst = NULL;
	arch = (void *)ptr + SARMAG;
	after_slash_size = get_archive_size(arch->ar_name);
	ranlib_size = (void *)ptr + sizeof(*arch) + SARMAG + after_slash_size;
	ran = (void *)ptr + SARMAG + sizeof(*arch) + after_slash_size + 4;
	ran_size = *((int*)ranlib_size);
	ran_size = ran_size / sizeof(struct ranlib);
	while (i < ran_size)
	{
		add_ran_offset(&lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
	process_archs(ptr, lst, filename);
	free_offset_lst(lst);
}