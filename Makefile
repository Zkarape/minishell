UNAME = $(shell uname -s)
NAME = minishell
CC = cc
CFLAGS =  -I ./readline-zkarapet/include -g -ggdb3 -Wall -Wextra  #-fsanitize=address
PREFIX = "${shell find ${HOME} -name readline-zkarapet 2>/dev/null}"
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

READLINE = -lreadline 

ifneq ($(UNAME), Linux)
	READLINE += -L readline-zkarapet/lib 
endif

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

lib:
	cd libft && make 

clean:
	rm -f ./*.o libft/*.o

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

readline:
	cd readline-master && ./configure --prefix=$(PREFIX)/ && make clean && make && make install

.PHONY: all clean fclean re lib readline
