#ifndef NM_H
#define NM_H

#define PROT PROT_READ | PROT_WRITE
#define ANON MAP_PRIVATE | MAP_ANONYMOUS
//# define BLOCK_SIZE sizeof(struct s_block)

#include "./libft.h"

typedef struct			s_symbols
{
	long int			adr_value;
	char				type;
	char				*name;
	struct s_symbols	*next;
	struct s_symbols	*prev;
}						t_symbols;

typedef struct 			s_section
{
	char				*name;
	unsigned int 		nb;
	struct s_section	*next;
}						t_section;

typedef struct 			s_lsection
{
	struct s_section	*first;
	struct s_section	*last;
}						t_lsection;

t_lsection *get_sections(char *ptr);

#endif
