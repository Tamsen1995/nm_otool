#include "../../includes/nm.h"

/*
** Will add a section element to the end of the section list
** This list is used to determine the type of an element
** of the type N_SECT
*/

void push_back(t_lsection *list, t_section *add)
{
	t_section *tmp;

	tmp = list->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	add->nb = tmp->nb + 1;
	list->last = add;
}

void add_to_list(char *sectname, t_lsection *list)
{

	t_section *add;

	if ((add = (t_section *)malloc(sizeof(t_section))) == NULL)
		return;
	add->next = NULL;
	add->name = ft_strdup(sectname);
	if (!list->first)
	{
		add->nb = 1;
		list->first = add;
		list->last = add;
	}
	else
		push_back(list, add);
}

void add_seg(struct load_command *lc, t_lsection *list)
{
	unsigned int i;
	struct segment_command_64 *seg;
	struct section_64 *sec;

	i = 0;
	seg = (struct segment_command_64 *)lc;
	sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
	while (i < seg->nsects)
	{
		add_to_list(sec->sectname, list);
		sec = (struct section_64 *)((void *)sec + sizeof(struct section_64));
		i++;
	}
}