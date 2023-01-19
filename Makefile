CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address -g
RM = rm -rf

NAME = pipex
BNAME = pipex_bonus

LIBFT = libft.a
LIBGNL = libgnl.a

LIBFT_DIR = libft/
LIBGNL_DIR = get_next_line/

SRC_FILES = 	pipex.c		\
				path.c		\
				free.c		\
				execute.c	\
				lst_utils.c	\
				error.c		\
				set_io.c

BSRC_FILES =	pipex_bonus.c		\
				path_bonus.c		\
				free_bonus.c		\
				execute_bonus.c		\
				lst_utils_bonus.c	\
				error_bonus.c		\
				set_io_bonus.c

SRC_DIR = mandatory/
BSRC_DIR = bonus/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
BSRC = $(addprefix $(BSRC_DIR), $(BSRC_FILES))

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
BOBJ = $(BSRC:$(BSRC_DIR)%.c=$(BOBJ_DIR)%.o)

OBJ_DIR = $(SRC_DIR)obj/
BOBJ_DIR = $(BSRC_DIR)obj/

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BOBJ_DIR)%.o:$(BSRC_DIR)%.c
	mkdir -p $(BOBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(LIBGNL)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBGNL) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)$(LIBFT) .

$(LIBGNL):
	$(MAKE) -C $(LIBGNL_DIR)
	mv $(LIBGNL_DIR)$(LIBGNL) .

all: $(NAME) bonus

bonus: $(BNAME)

$(BNAME): $(BOBJ) $(LIBFT) $(LIBGNL)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBFT) $(LIBGNL) -o $(BNAME)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BOBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBGNL_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BNAME)
	$(RM) $(LIBFT)
	$(RM) $(LIBGNL)

re: fclean all

.PHONY: bonus