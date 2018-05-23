#ifndef NM_H
#define NM_H

#define PROT PROT_READ | PROT_WRITE
#define ANON MAP_PRIVATE | MAP_ANONYMOUS
//# define BLOCK_SIZE sizeof(struct s_block)

# include "./libft.h"
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

typedef struct			s_symbols
{
	long int			value;
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


void ft_nm(char *ptr);
void handle_64(char *ptr);
t_lsection *get_sections_64(char *ptr);

void handle_fat(char *ptr);

void add_seg(struct load_command *lc, t_lsection *list);
void process_symtab(struct symtab_command *sym, char *ptr, t_lsection *sec_list);
void add_symbols(char *strable, struct nlist_64 list, t_lsection *sec_list, t_symbols **sym_list);

t_symbols *add_before(t_symbols *add_bef_this, t_symbols *add);
uint32_t swap_uint32(uint32_t val);
t_symbols *bubble_sort(t_symbols *sym_list);

/*
Testing functions
*/

void print_symbols(t_symbols *sym_list);
void print_syms_prev(t_symbols *sym_list);

#endif
