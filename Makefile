# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonniss <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/19 14:34:59 by abonniss          #+#    #+#              #
#    Updated: 2022/02/19 14:35:04 by abonniss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = philosphers

#COMPILER
CC = clang

#COMPILER FLAGS
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pthread

#ERROR FLAGS
ifneq ($(err), no)
	CFLAGS += -Werror
endif

#DEBUG FLAGS
ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address
else ifeq ($(debug), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -Weverything
endif

#DEBUGS SYMBOLS
DSYM += $(NAME).dSYM 

#INCLUDES 
INCLUDES += includes

#PATH_SOURCES 
PATH_SRCS = srcs

#SOURCES
SRCS += philosophers.c
SRCS += utils.c

#HEADERS
HEADERS += philosophers.h

#VPATH
vpath %.c $(PATH_SRCS)
vpath %.h $(INCLUDES)

#OBJS
PATH_OBJS = objs
OBJS = $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

#COLORS PRINT
NC 		= \033[0m
GREEN 	= \033[32m
CYAN 	= \033[36m
RED 	= \033[31m
ONELINE = \e[1A\r


#RULES 

all: $(NAME)

$(NAME): $(PATH_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES) -o $@
	printf "$(GREEN)$@ IS READY\n$(NC)"

FORCE: 
	#permet de forcer la réalisationn de la lib

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	printf "$(CYAN)$< IS COMPILING                                 \n$(NC)"

$(PATH_OBJS):
	mkdir $@

clean:
	$(RM) -R $(PATH_OBJS) $(DSYM)
	printf "$(RED)IT'S CLEAN\n$(NC)"

fclean: clean
	$(RM) $(NAME)
	printf "$(RED)$(NAME) REMOVED\n$(NC)"

re: fclean
	$(MAKE)

.PHONY: clean fclean re all FORCE 

.SILENT: 