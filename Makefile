# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 22:03:00 by scarboni          #+#    #+#              #
#    Updated: 2022/07/07 19:09:01 by scarboni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

DCOLORS :=  	$($(RESET))='$(RESET)'\
				$($(BLACK))='$(BLACK)'\
				$($(RED))='$(RED)'\
				$($(GREEN))='$(GREEN)'\
				$($(YELLOW))='$(YELLOW)'\
				$($(BLUE))='$(BLUE)'\
				$($(MAGENTA))='$(MAGENTA)'\
				$($(CYAN))='$(CYAN)'\
				$($(WHITE))='$(WHITE)'\
				$($(BOLDBLACK))='$(BOLDBLACK)'\
				$($(BOLDRED))='$(BOLDRED)'\
				$($(BOLDGREEN))='$(BOLDGREEN)'\
				$($(BOLDYELLOW))='$(BOLDYELLOW)'\
				$($(BOLDBLUE))='$(BOLDBLUE)'\
				$($(BOLDMAGENTA))='$(BOLDMAGENTA)'\
				$($(BOLDCYAN))='$(BOLDCYAN)'\
				$($(BOLDWHITE))='$(BOLDWHITE)'

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
TESTPARSERRULE			= testParserRule
TESTPARSER				= testParser
TESTDISPATCHRULE		= testDispatchRule
TESTDISPATCH			= testDispatch


ALL_RULES_NAMES =		$(CLEAN_UNWANTED_PATHS) \
						$(SAVE_LAST_LOGS) \
						$(CLEAN_LOGS) \
						$(COMPILE) 

ALL_EXECS_NAMES =		$(NAME)\
						$(TESTPARSER)\
						$(TESTDISPATCH)

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


# USER_PATH	=	User/
# USER_FILES 	= 	User
# SRCS_FILES 		+=	$(addprefix $(USER_PATH), $(USER_FILES))

# CHANNEL_PATH	=	Channel/
# CHANNEL_FILES 	= 	Channel

# SRCS_FILES 		+=	$(addprefix $(CHANNEL_PATH), $(CHANNEL_FILES))

NETWORK_PATH	=	network/
NETWORK_FILES 	= 	MasterServer \
					Client
SRCS_FILES 		+=	$(addprefix $(NETWORK_PATH), $(NETWORK_FILES))
					
SERVER_PATH		=	IrcServer/
SERVER_FILES 	= 	IRCServer
SRCS_FILES 		+=	$(addprefix $(SERVER_PATH), $(SERVER_FILES))

COMMAND_PATH	=	Execute_command/
COMMAND_FILES 	= 	example_command \
					NICK \
					PASS \
					PRIVMSG \
					USER \
					ignore_command

SRCS_FILES 		+=	$(addprefix $(COMMAND_PATH), $(COMMAND_FILES))

UTIL_PATH		=	util/
UTIL_FILES 		=	parse \
					numbers \
					compareContainers \
					containerTo \
					logger \
					CodeBuilder
SRCS_FILES 		+=	$(addprefix $(UTIL_PATH), $(UTIL_FILES))

#
# -------------------------------- Building configurations --------------------------------
#

CXX				= c++
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address -MD
CPPFLAGS 		+= -DLOGS_FOLDER='"$(LAST_RUN_LOGS_FOLDER)"'

RM				= rm -f
CPPFLAGS		+= $(DCOLORS)
# CPPFLAGS		+= -DGRAMMAR_FILE='"./grammar/grammar.gram"'

LDFLAGS			= -I$(INC_DIR)
TESTERS_FLAGS	= -DDEBUG=true
#
# -------------------------------- automated tests treatments --------------------------------
#

ifndef TESTS 
	TESTS=""
	SRCS_FILES += 	main
else
	ifeq ($(TESTS), $(TESTPARSERRULE))
		NAME_TESTER=$(TESTPARSER)
		SRCS_FILES += $(TEST_SRCS)mainParserTest
	else
		ifeq ($(TESTS), $(TESTDISPATCHRULE))
			NAME_TESTER=$(TESTDISPATCH)
			SRCS_FILES += $(TEST_SRCS)mainDispatchTest
		endif
	endif
endif


ifndef LEAKS
	LEAKS = 
	# LEAKS = valgrind --leak-check=full #must not be use at the same time than fsanitize
endif


TESTER_OBJ_EXT		=o_tester.o

SRCS_FILES_EXT 		+= 	$(addsuffix $(CPP_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=o))
OBJS_TESTER			= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=$(TESTER_OBJ_EXT)))
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

define tester_sep
	printf "\n\n\n\n____.--.--.____.--.--.____.--.--.____.--.--.__** $(1) **__.--.--.____.--.--.____.--.--.____.--.--.____\n" ;\
	$(MAKE) $(2) TESTS=$(1)  ;\
	$(MAKE) $(1) TESTS=$(1) LEAKS="$(LEAKS)"
endef

define launch_one_test_without_sep
	printf "Command : $(LEAKS) ./$(NAME_TESTER) $(1) \n"  ;\
	$(LEAKS) ./$(NAME_TESTER) $(1)
endef

define launch_one_test_with_sep
	$(call launch_one_test_without_sep,$(1)) ;\
	printf "____.--.--.____.--.--.____.--.--.____.--.--.__Weeeeeeeeee__.--.--.____.--.--.____.--.--.____.--.--.____\n"
endef

define launch_only_legal_tests
	@ if [ $(TESTS) = $(1) ]; then \
		$(3)
	else \
		$(call tester_sep,$(1), $(2)) ;\
	fi ;
endef

define launch_test_from_array_args
	COUNT=0;\
	for ARG in $(1) ; do \
		COUNT=$$(( 1 + $$COUNT ));\
		LAST=$$ARG;\
		[ "$(words $(1))" -eq $$COUNT ] && break ;\
		$(call launch_one_test_with_sep,$$ARG) ;\
	done ;\
	$(call launch_one_test_without_sep,$$LAST)
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
	${CXX} ${CPPFLAGS} $(LDFLAGS) -DDEBUG=false -c $< -o $@
	${CXX} ${CPPFLAGS} ${TESTERS_FLAGS} $(LDFLAGS) -c $< -o $@_tester.o

# $(COMPILE): $(OBJS)
# 	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(NAME_TESTER): | $(CLEAN_UNWANTED_PATHS) $(ALL_PATHS_TO_INIT) $(OBJS)
	$(CXX) $(CPPFLAGS) ${TESTERS_FLAGS} $(LDFLAGS) -o $(NAME_TESTER) $(OBJS_TESTER)

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

REQUESTS_FOLDER=test_datas/generated/
CLIENTS_REQUESTS:= $(addprefix $(REQUESTS_FOLDER), $(shell ls $(REQUESTS_FOLDER)))

$(TESTDISPATCHRULE):
	$(call launch_only_legal_tests,$(TESTDISPATCHRULE),$(TESTDISPATCH),\
		$(call launch_test_from_array_args,$(CLIENTS_REQUESTS)) ;\)

$(TESTPARSERRULE):
	$(call launch_only_legal_tests,$(TESTPARSERRULE),$(TESTPARSER),\
		$(call launch_test_from_array_args,$(CLIENTS_REQUESTS)) ;\)


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
.DEFAULT_GOAL := all