
CC = gcc
FLAGS = -g -Wall -Wextra -Werror -I includes
PRINTF = libft/printf/libftprintf.a
LIBFT = libft/libft.a
NAME_nm = ft_nm
SRC_nm = src/handle_fat.c \
	src/symbol_adding.c \
	src/swap_bytes.c \
	src/sorting_algs.c \
	src/nm/main_nm.c \
	src/nm/det_type.c \
	src/nm/ft_nm.c \
	src/nm/add_to_list.c \
	src/nm/print_symbols.c \
	src/nm/case_64/get_sections_64.c \
	src/nm/case_64/handle_64.c \
	src/nm/case_64/process_symtab_64.c \
	src/nm/case_64/add_symbols_64.c \
	src/nm/case_32/get_sections_32.c \
	src/nm/case_32/handle_32.c \
	src/nm/case_32/process_symtab_32.c \
	src/nm/case_32/add_symbols_32.c \
	src/nm/del_symbols.c \
	src/testing/print_syms_prev.c \



OBJ_nm = $(addsuffix .o, $(basename $(SRC_nm)))

all: $(LIBFT) $(NAME_nm)

$(LIBFT):
	make -C libft

$(NAME_nm):$(LIBFT) $(NAME_nm) $(OBJ_nm)
	@echo "building binary file"
	$(CC) $(FLAGS) $(SRC_nm) -o $(NAME_nm) -I -lft $(LIBFT) $(PRINTF)

%.o: %.c ft_ls.h
		clang $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ_nm)
	@make clean -C libft/

fclean: clean
	@echo "delete $(NAME_nm)"
	@rm -f $(NAME_nm)
	@rm -rf ft_nm.dSYM
	@make fclean -C libft/

re: fclean all

.PHONY: re clean fclean all