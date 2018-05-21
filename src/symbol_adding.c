#include "../includes/nm.h"

void add_before(t_symbols *add_bef_this, t_symbols *add)
{
	t_symbols *tmp;

	// save the prev 
	tmp = add_bef_this->prev;

	// point the next of the item before to the new item
	if (add_bef_this->prev)
		add_bef_this->prev->next = add;

	// 
	add_bef_this->prev = add;
	add->next = add_bef_this;
	add->prev = tmp;




}