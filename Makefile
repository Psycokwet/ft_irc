INC_DIR		= .

SRCS		=	./srcs/main.cpp \
				./srcs/network/MasterServer.cpp \
				./srcs/network/Client.cpp \
				./srcs/Channel/Channel.cpp \
				./srcs/Users/Users.cpp \
				./srcs/IrcServer/IRCServer.cpp

OBJS		= $(SRCS:.cpp=.o)

NAME		= ircserv

CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

RM			= rm -f

.cpp.o:
			@$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			@echo "Object files compiled"
			@$(CC) $(FLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)
			@echo "Executable created"
			@echo "Compilation finished"

all:		$(NAME)

clean:
			@$(RM) $(OBJS)
			@echo "Deleted all but executable"

fclean:		clean
			@$(RM) $(NAME)
			@echo "Everything deleted"

re:			fclean all

.PHONY:		all clean fclean re
