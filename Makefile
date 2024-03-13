SRC = \
	main.c\
	tokenise.c\
	escape_quoted.c\
	expand_variables.c\
	strnesc.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

NAME = minishell

CFLAGS = -Werror -Wall -Wextra

all : libft/libft.a $(OBJ_DIR) $(NAME)

libft/ :
	git clone git@github.com:slink7/libft.git

libft/libft.a : libft/
#	git submodule update --init --remote
	cd libft/ ; make

clean :
	rm -rf $(OBJ_DIR) || true

fclean : clean
	rm $(NAME) || true

re : fclean all

$(NAME) : $(OBJ)
	cc -o $(NAME) $(OBJ) -Llibft -lft -lreadline

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	cc -g3 $(CFLAGS) -o $@ -c $< -Ilibft/