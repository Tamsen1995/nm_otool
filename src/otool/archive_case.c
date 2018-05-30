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
}

/*
** handles the archive case
*/

void go_archive(char *ptr)
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
	ran = (void *)ptr + SARMAG + sizeof(*arch) + 4;
	ranlib_size = (void *)ptr + SARMAG + sizeof(*arch);
	ran_size = (int)(*ranlib_size);
	ran_size = ran_size / sizeof(struct ranlib);

	// iterate through the ranlibs and put all the crucial info into a linked list
	// crucial information I'll need the ran[i].ran_off which is the offset
	// I also need the ran[].ran_un.ran_strx which is the string table index
	while (i < ran_size)
	{
		add_ran_offset(&lst, ran[i].ran_off, ran[i].ran_un.ran_strx);
		i++;
	}
//	handle_archs(lst);
	exit(0); // TESTING
}