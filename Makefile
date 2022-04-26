CC = gcc
AR = ar rcs
REMOVE = rm -f
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = get_next_line.c get_next_line_utils.c
BONUS_SRC_FILES = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_SRC_FILES:.c=.o)

HEADER_FILES = libft.h
BONUS_HEADER_FILES = libft_bonus.h

NAME = get_next_line

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

bonus: $(NAME:=_bonus)

$(NAME:=_bonus): $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJ_FILES)
	cp $@ $(NAME)

%_bonus.o: %_bonus.c $(BONUS_HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	$(REMOVE) $(NAME) $(NAME:=_bonus)

re:	fclean all

norm:
	norminette

.PHONY: all bonus clean fclean norm re
