# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejjeong <sejjeong@student.42gyeongsan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 16:33:48 by sejjeong          #+#    #+#              #
#    Updated: 2026/01/05 02:13:16 by sejjeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
C++ = c++
FLAGS= -Wall -Wextra -Werror

RM = rm
RM_FLAGS = -rf

SRCS_DIR = .
CORE_DIR = $(SRCS_DIR)/core
COMMAND_DIR = $(SRCS_DIR)/command
PARSER_DIR = $(SRCS_DIR)/parser
BOT_DIR = $(SRCS_DIR)/bot
INCLUDE = -I $(CORE_DIR) -I $(COMMAND_DIR) -I $(PARSER_DIR)

SRCS = $(SRCS_DIR)/main.cpp \
		$(CORE_DIR)/Channel.cpp \
		$(CORE_DIR)/Lobby.cpp \
		$(CORE_DIR)/LoggedInSpace.cpp \
		$(CORE_DIR)/LoginInfo.cpp \
		$(CORE_DIR)/Server.cpp \
		$(CORE_DIR)/Space.cpp \
		$(CORE_DIR)/User.cpp \
		$(CORE_DIR)/Util.cpp \
		$(CORE_DIR)/MessageBetch.cpp \
		$(COMMAND_DIR)/CommonCommand.cpp \
		$(COMMAND_DIR)/DirectMessageCommand.cpp \
		$(COMMAND_DIR)/ErrorCommand.cpp \
		$(COMMAND_DIR)/InviteCommand.cpp \
		$(COMMAND_DIR)/JoinCommand.cpp \
		$(COMMAND_DIR)/KickCommand.cpp \
		$(COMMAND_DIR)/ListCommand.cpp \
		$(COMMAND_DIR)/ModeCommand.cpp \
		$(COMMAND_DIR)/NickCommand.cpp \
		$(COMMAND_DIR)/PartCommand.cpp \
		$(COMMAND_DIR)/PassCommand.cpp \
		$(COMMAND_DIR)/QuitCommand.cpp \
		$(COMMAND_DIR)/SendChannelMessageCommand.cpp \
		$(COMMAND_DIR)/TopicCommand.cpp \
		$(COMMAND_DIR)/UserCommand.cpp \
		$(COMMAND_DIR)/WhoCommand.cpp \
		$(PARSER_DIR)/Parser.cpp


OBJS = ${SRCS:.cpp=.o}

$(NAME): $(OBJS)
			make -C $(BOT_DIR)
		   $(C++) $(FLAGS) $(INCLUDE) $^ -o $@

%.o: %.cpp
	$(C++) $(FLAGS) $(INCLUDE) -c $< -o $@ 

all: $(NAME)
	

clean:
	make -C $(BOT_DIR) clean
	$(RM) $(RM_FLAGS) $(OBJS)

fclean: clean
	make -C $(BOT_DIR) fclean
	$(RM) $(RM_FLAGS) $(NAME)

re: fclean all	
	make -C $(BOT_DIR) re
.PHONY: all re clean fclean 
