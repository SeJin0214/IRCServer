# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejjeong <sejjeong@student.42gyeongsan>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 16:33:48 by sejjeong          #+#    #+#              #
#    Updated: 2025/04/02 12:50:08 by sejjeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
C++ = c++
FLAGS= -Wall -Wextra -Werror -std=c++98

RM = rm
RM_FLAGS = -rf

SRCS_DIR = .
CORE_DIR = $(SRCS_DIR)/core
COMMAND_DIR = $(SRCS_DIR)/command
INCLUDE = -I $(SRCS_DIR)/core -I $(SRCS_DIR)/command 

SRCS = $(SRCS_DIR)/main.cpp \
		$(CORE_DIR)/Server.cpp \
		$(CORE_DIR)/Space.cpp \
		$(CORE_DIR)/Channel.cpp \
		$(CORE_DIR)/User.cpp \
		$(CORE_DIR)/Lobby.cpp \
		$(CORE_DIR)/Util.cpp \
		$(COMMAND_DIR)/BroadcastCommand.cpp \
		$(COMMAND_DIR)/HelpCommand.cpp \
		$(COMMAND_DIR)/ChannelListCommand.cpp \
		$(COMMAND_DIR)/DirectMessageCommand.cpp \
		$(COMMAND_DIR)/InviteCommand.cpp \
		$(COMMAND_DIR)/KickCommand.cpp \
		$(COMMAND_DIR)/SendChannelMessageCommand.cpp \


OBJS = ${SRCS:.cpp=.o}

$(NAME): $(OBJS)
		   $(C++) $(FLAGS) $(INCLUDE) $^ -o $@

%.o: %.cpp
	$(C++) $(FLAGS) $(INCLUDE) -c $< -o $@ 

all: $(NAME)

clean:
	$(RM) $(RM_FLAGS) $(OBJS)

fclean: clean
	$(RM) $(RM_FLAGS) $(NAME)

re: fclean all
	
.PHONY: all re clean fclean 
