
NAME = ft_ls

SRC_NAME = main.c \
args_separate_sort.c \
args_long_form.c \
btree.c \
build_btree.c \
btree_sort_branch.c \
btree_long_form.c \
helpers_1.c \
helpers_2.c \
print_long_form_helpers.c \
options.c \
path.c \
checks.c \
time.c \
devices.c \
print_helpers.c \
error.c \

SRC_DIR = src/

LIB_DIR = lib/

OBJ_DIR = obj/

INCLUDES = includes/

SRCS = $(addprefix $(SRC_DIR),$(SRC_NAME))

OBJ = $(subst .c,.o,$(SRC_NAME))

OBJECTS = $(addprefix $(OBJ_DIR),$(OBJ))

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C $(LIB_DIR)
	gcc -c $(FLAGS) $(SRCS) -I $(INCLUDES)
	mkdir -p $(OBJ_DIR)
	mv -f $(OBJ) $(OBJ_DIR)
	gcc $(FLAGS) $(OBJECTS) -I $(INCLUDES) -L $(LIB_DIR) -lft -o $(NAME)

clean:
	make clean -C $(LIB_DIR)
	/bin/rm -f $(OBJECTS)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)
	/bin/rm -f $(NAME)

re: fclean all
