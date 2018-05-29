#include "../../includes/nm.h"

/*
** creates a new sections element
** chooses the appropiate architecture by checking to see
** which of the two params are set to NULL
*/

t_section_list *create_sec(struct section *sec, struct section_64 *sec_64)
{
	t_section_list *new;

	new = NULL;
	if (!(new = (t_section_list *)malloc(sizeof(t_section_list))))
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->section_32 = NULL;
	new->section_64 = NULL;
	if (sec)
		new->section_32 = sec;
	else if (sec_64)
		new->section_64 = sec_64;
	return (new);
}

/*
** adds a section into the linked list responsible for sections
** it determines the architecture of the section element
** by looking at the two section parameters
** if one of them is NULL
** then that means the other one shall be added to the list
*/

void add_sec(t_section_list **sec_list, struct section *sec, struct section_64 *sec_64)
{
	t_section_list *tmp;
	t_section_list *new;

	tmp = (*sec_list);
	new = create_sec(sec, sec_64);
	if (!(*sec_list))
	{
		(*sec_list) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	// then iterate to the end and simply add it
}