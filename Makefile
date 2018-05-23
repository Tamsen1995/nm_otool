ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc
FLAGS = -g -Wall -Wextra -Werror -I includes
PRINTF = libft/printf/libftprintf.a
LIBFT = libft/libft.a
NAME = ft_nm
SRC = src/main.c \
	src/det_type.c \
	src/ft_nm.c \
	src/handle_fat.c \
	src/symbol_adding.c \
	src/swap_bytes.c \
	src/sorting_algs.c \
	src/nm/add_to_list.c \
	src/nm/case_64/get_sections_64.c \
	src/nm/case_64/handle_64.c \
	src/nm/case_64/process_symtab_64.c \
	src/nm/case_64/add_symbols_64.c \
	src/nm/case_32/get_sections_32.c \
	src/nm/case_32/handle_32.c \
	src/nm/case_32/process_symtab_32.c \
	src/nm/case_32/add_symbols_32.c \
	src/nm/del_symbols.c \
	src/testing/print_symbols.c \
	src/testing/print_syms_prev.c \



OBJ = $(addsuffix .o, $(basename $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME):$(LIBFT) $(NAME) $(OBJ)
	@echo "building binary file"
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -I -lft $(LIBFT) $(PRINTF)

%.o: %.c ft_ls.h
		clang $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C libft/

fclean: clean
	@echo "delete $(NAME)"
	@rm -f $(NAME)
	@rm -rf ft_nm.dSYM
	@make fclean -C libft/

re: fclean all

.PHONY: re clean fclean all