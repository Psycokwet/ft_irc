# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idamouttou <idamouttou@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 22:03:00 by scarboni          #+#    #+#              #
#    Updated: 2022/06/24 13:48:49 by idamouttou       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./srcs/main.cpp \
				./srcs/network/MasterServer.cpp \
				./srcs/network/Client.cpp \
				./srcs/Channel/Channel.cpp \
				./srcs/User/User.cpp \
				./srcs/IRCServer/IRCUSER.cpp \
				./srcs/IrcServer/IRCServer.cpp
#
# -------------------------------- Paths --------------------------------
#

RESET			= "\033[0m"
BLACK			= "\033[30m"
RED				= "\033[31m"
GREEN			= "\033[32m"
YELLOW			= "\033[33m"
BLUE			= "\033[34m"
MAGENTA			= "\033[35m"
CYAN			= "\033[36m"
WHITE			= "\033[37m"
BOLDBLACK		= "\033[1m\033[30m"
BOLDRED			= "\033[1m\033[31m"
BOLDGREEN		= "\033[1m\033[32m"
BOLDYELLOW		= "\033[1m\033[33m"
BOLDBLUE		= "\033[1m\033[34m"
BOLDMAGENTA		= "\033[1m\033[35m"
BOLDCYAN		= "\033[1m\033[36m"
BOLDWHITE		= "\033[1m\033[37m"

$(RESET)		= RESET
$(BLACK)		= BLACK
$(RED)			= RED
$(GREEN)		= GREEN
$(YELLOW)		= YELLOW
$(BLUE)			= BLUE
$(MAGENTA)		= MAGENTA
$(CYAN)			= CYAN
$(WHITE)		= WHITE
$(BOLDBLACK)	= BOLDBLACK
$(BOLDRED)		= BOLDRED
$(BOLDGREEN)	= BOLDGREEN
$(BOLDYELLOW)	= BOLDYELLOW
$(BOLDBLUE)		= BOLDBLUE
$(BOLDMAGENTA)	= BOLDMAGENTA
$(BOLDCYAN)		= BOLDCYAN
$(BOLDWHITE)	= BOLDWHITE

COLORS = 		$($(RESET))\
				$($(BLACK))\
				$($(RED))\
				$($(GREEN))\
				$($(YELLOW))\
				$($(BLUE))\
				$($(MAGENTA))\
				$($(CYAN))\
				$($(WHITE))\
				$($(BOLDBLACK))\
				$($(BOLDRED))\
				$($(BOLDGREEN))\
				$($(BOLDYELLOW))\
				$($(BOLDBLUE))\
				$($(BOLDMAGENTA))\
				$($(BOLDCYAN))\
				$($(BOLDWHITE))

DCOLORS :=  	$($(RESET))=$(RESET)\
				$($(BLACK))=$(BLACK)\
				$($(RED))=$(RED)\
				$($(GREEN))=$(GREEN)\
				$($(YELLOW))=$(YELLOW)\
				$($(BLUE))=$(BLUE)\
				$($(MAGENTA))=$(MAGENTA)\
				$($(CYAN))=$(CYAN)\
				$($(WHITE))=$(WHITE)\
				$($(BOLDBLACK))=$(BOLDBLACK)\
				$($(BOLDRED))=$(BOLDRED)\
				$($(BOLDGREEN))=$(BOLDGREEN)\
				$($(BOLDYELLOW))=$(BOLDYELLOW)\
				$($(BOLDBLUE))=$(BOLDBLUE)\
				$($(BOLDMAGENTA))=$(BOLDMAGENTA)\
				$($(BOLDCYAN))=$(BOLDCYAN)\
				$($(BOLDWHITE))=$(BOLDWHITE)

DCOLORS :=  	$(addprefix -D, $(DCOLORS))

#
# -------------------------------- Paths --------------------------------
#

INC_DIR					= .

LAST_RUN_LOGS_FOLDER	= logs
SAVED_LOGS_FOLDER		= pastLogs

TEST_SRCS				= test_srcs/
TEST_DATAS				= test_datas/
TEST_DATAS_GENERATED	= $(TEST_DATAS)generated/

OBJ_PATH				= bin/

SRC_PATH				= srcs/

CPP_EXTENSION 			= .cpp

UTIL_PATH				= util/
NETWORK_PATH			= network/
SERVER_PATH				= IrcServer/

OBJ_PATHS				+= $(OBJ_PATH) $(addprefix $(OBJ_PATH), $(UTIL_PATH) $(NETWORK_PATH) $(SERVER_PATH) )

ALL_PATHS_TO_INIT		= $(SAVED_LOGS_FOLDER) $(LAST_RUN_LOGS_FOLDER)

#
# -------------------------------- Rules names --------------------------------
#

CLEAN_UNWANTED_PATHS 	= CleanPreviousPaths
SAVE_LAST_LOGS 			= SaveLastLogs
NAME					= ircserv
CLEAN_LOGS				= cleanLogs
COMPILE 				= compile


ALL_RULES_NAMES =		$(CLEAN_UNWANTED_PATHS) \
						$(SAVE_LAST_LOGS) \
						$(CLEAN_LOGS) \
						$(COMPILE)

ALL_EXECS_NAMES =		$(NAME)

#
# -------------------------------- TEST SRCS definitions --------------------------------
#

GENERATE_EXAMPLES_REQUESTS_FILES = 	writeRequestsExamples

GENERATE_EXAMPLES_REQUESTS_SRCS_RAW += $(addprefix $(TEST_SRCS), $(GENERATE_EXAMPLES_REQUESTS_FILES))
GENERATE_EXAMPLES_REQUESTS_SRCS_RAW += $(UTIL_PATH)logger

GENERATE_EXAMPLES_REQUESTS_SRCS_EXT = $(addsuffix  $(CPP_EXTENSION), $(GENERATE_EXAMPLES_REQUESTS_SRCS_RAW))

GENERATE_EXAMPLES_REQUESTS_SRCS = $(addprefix  $(SRC_PATH), $(GENERATE_EXAMPLES_REQUESTS_SRCS_EXT))
#
# -------------------------------- SRCS definitions --------------------------------
#

NETWORK_FILES = 	MasterServer \
					Client
SRCS_FILES += $(addprefix $(NETWORK_PATH), $(NETWORK_FILES))
					
SERVER_FILES = 	IRCServer
SRCS_FILES += $(addprefix $(SERVER_PATH), $(SERVER_FILES))

UTIL_FILES =	parse \
				numbers \
				logger
SRCS_FILES += $(addprefix $(UTIL_PATH), $(UTIL_FILES))

#
# -------------------------------- Building configurations --------------------------------
#

CXX				= c++
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address -MD
CPPFLAGS 		+= -DLOGS_FOLDER='"$(LAST_RUN_LOGS_FOLDER)"'

RM				= rm -f
CPPFLAGS		+= $(DCOLORS)

LDFLAGS			= -I$(INC_DIR)

#
# -------------------------------- automated tests treatments --------------------------------
#

ifndef LEAKS
	LEAKS = 
	# LEAKS = valgrind --leak-check=full #must not be use at the same time than fsanitize
endif

ifndef TESTS
	TESTS=""
	SRCS_FILES += 	main
	CPPFLAGS += -DDEBUG=false
else
	CPPFLAGS += -DDEBUG=true
endif

SRCS_FILES_EXT 		+= 	$(addsuffix $(CPP_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=o))
DEPS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=d))
-include $(DEPS)

#
# -------------------------------- FUNCTIONS --------------------------------
#

define colorize
	@echo -n $(1)
	@$(2)
	@echo -n $(RESET)
endef

#
# -------------------------------- Rules implementations --------------------------------
#

#
## -------------------------------- COMPILE --------------------------------
#
all: | $(CLEAN_UNWANTED_PATHS) $(ALL_PATHS_TO_INIT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp 

	@mkdir -p $(dir $@)
	${CXX} ${CPPFLAGS} $(LDFLAGS) -c $< -o $@

# $(COMPILE): $(OBJS)
# 	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(NAME):  $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

#
## -------------------------------- LOGS --------------------------------
#

$(SAVE_LAST_LOGS)	:
	$(call colorize, $(GREEN), \
		echo "Saving previous logs" ;\
		mv  $(LAST_RUN_LOGS_FOLDER)  $(SAVED_LOGS_FOLDER)/$(shell date "+%y_%m_%d_%H_%M_%S") ;\
	)


$(CLEAN_UNWANTED_PATHS)	: 
	$(call colorize, $(YELLOW), \
		echo "deleting previous run special paths..." $(LAST_RUN_LOGS_FOLDER) ;\
		rm -rf  $(LAST_RUN_LOGS_FOLDER) ;\
	)
	

#
## -------------------------------- TESTS --------------------------------
#

generateParsingTestFiles :
	@echo "Deleting previous generation..."
	@rm -rf $(TEST_DATAS_GENERATED)
	@mkdir -pv $(TEST_DATAS_GENERATED)
	@echo "Attempting generation"
	@$(CXX)  $(GENERATE_EXAMPLES_REQUESTS_SRCS)  $(CPPFLAGS) 
	@./a.out $(TEST_DATAS_GENERATED)
	@echo "Cleaning intermediate tools..."
	@$(RM) ./a.out

#
## -------------------------------- OTHERS --------------------------------
#

$(ALL_PATHS_TO_INIT): 

	$(call colorize, $(GREEN), \
		echo "Generating bin folder and subfolders" $@ ;\
		mkdir -p  $@   ;\
	)
	

$(CLEAN_LOGS):
	$(call colorize, $(YELLOW), \
		echo "Deleting last logs...";\
		rm -rf $(LAST_RUN_LOGS_FOLDER);\
	)
	
clean:  $(CLEAN_LOGS)
	$(call colorize, $(RED), \
		echo "Deleting objects...";\
		rm -rf $(OBJ_PATH);\
		echo "Deleted all but executable";\
	)

fclean:		clean
	$(call colorize, $(BOLDRED), \
		$(RM) $(ALL_EXECS_NAMES);\
		echo "Everything deleted";\
	)

re:			fclean all

.PHONY:		all clean fclean re $(ALL_RULES_NAMES)
