ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC = gcc
FLAGS = -g -Wall -Wextra -Werror -I includes
LIBFT = libft/libft.a
NAME = ft_nm
SRC = main.c \
	get_sections.c \


OBJ = $(addsuffix .o, $(basename $(SRC)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME):$(LIBFT) $(NAME) $(OBJ)
	@echo "building binary file"
	$(CC) $(FLAGS) $(SRC) -o $(NAME) -I -lft $(LIBFT)

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