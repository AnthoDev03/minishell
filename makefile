CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

EXEC = minishell

SRC = srcs/main.c srcs/lexer/lexer.c srcs/parser/parser.c \
	  srcs/expander/expander.c srcs/executor/executor.c     \
		srcs/built-in/env.c srcs/built-in/cd.c srcs/built-in/echo.c \
		srcs/built-in/exit.c srcs/built-in/export.c srcs/built-in/pwd.c \
		srcs/built-in/unset.c srcs/utils/utils1.c srcs/built-in/export2.c \
		srcs/executor/executor2.c srcs/executor/executor3.c srcs/executor/executor4.c \
		srcs/expander/expander2.c srcs/parser/parser2.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re
