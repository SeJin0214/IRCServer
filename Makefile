
NAME = ircserv
C++ = c++
FLAGS= -Wall -Wextra -Werror -std=c++98

RM = rm
RM_FLAGS = -rf

SRCS_DIR = .

SRCS = $(SRCS_DIR)/main.cpp \
	   $(SRCS_DIR)/Server.cpp \
	   $(SRCS_DIR)/Util.cpp \

OBJS = ${SRCS:.cpp=.o}

$(NAME): $(OBJS)
		   $(C++) $(FLAGS) $^ -o $@

%.o: %.cpp
	$(C++) $(FLAGS) -c $< -o $@ 

all: $(NAME)

clean:
	$(RM) $(RM_FLAGS) $(OBJS)

fclean: clean
	$(RM) $(RM_FLAGS) $(NAME)

re: fclean all
	
.PHONY: all re clean fclean 