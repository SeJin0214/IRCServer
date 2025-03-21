SRCS = main.cpp Server.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++
OBJS = $(SRCS:.cpp=.o)
NAME = ircserv

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re