#include "../includes/nm.h"

t_symbols *add_before(t_symbols *add_bef_this, t_symbols *add)
{
	t_symbols *tmp;
	t_symbols *ret;

	ret = NULL;
	tmp = NULL;
	if (add_bef_this->prev == NULL)
		ret = add;
	tmp = add_bef_this->prev;
	if (add_bef_this->prev)
		add_bef_this->prev->next = add;
	add_bef_this->prev = add;
	add->next = add_bef_this;
	add->prev = tmp;
	return (ret);
}