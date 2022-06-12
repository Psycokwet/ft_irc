NAME = ircserv

INC_DIR		= .

CC = 		C++

CFLAGS = 	-Wall -Werror -Wextra -std=c++98
RM = 		rm -rf

SRCS =	./srcs/main.cpp \
			./srcs/network/Server.cpp

OBJS		= $(SRCS:.cpp=.o)

.cpp.o:
			@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(<:.cpp=.o)

$(NAME):	$(OBJS)
			@echo "Object compiled"
			@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -o $(NAME)
			@echo "Executable ok"
			@echo "finish"

all:		$(NAME)

clean:
			@$(RM) $(OBJS)
			@echo "Clean ok"

fclean:		clean
			@$(RM) $(NAME)
			@echo "fclean ok"

re:			fclean all

.PHONY:		all clean fclean re