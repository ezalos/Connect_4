# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 15:04:16 by ldevelle          #+#    #+#              #
#    Updated: 2019/09/29 02:57:42 by ezalos           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= Connect_4

CC = gcc

CFLAGS = -Wall -Wextra -Werror

DFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g3 -pedantic\
-O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int\
-Werror-implicit-function-declaration -Wmain -Wparentheses -Wsequence-point\
-Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas\
-Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast\
-Wwrite-strings -Wconversion -Wsign-compare -Waggregate-return\
-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
-Wmissing-noreturn -Wformat -Wmissing-format-attribute\
-Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs\
-Winline -Wlong-long -Wunreachable-code

# CFLAGS = $(DFLAGS)
CFLAGS =

##############################################################################
##############################################################################
##																			##
##									----									##
##									IFEQ									##
##									----									##
##																			##
##############################################################################
##############################################################################

SRCS_LI		=			main\
						print\
						engine\
						init\
						check_win\
						db_tree\
						save_tree\
						input



SRC_PATH	= ./srcs

DIR_OBJ 	= ./objs/

##########################
##						##
##	   ARCHITECTURE		##
##						##
##########################

A_SRC 		= $(patsubst %,$(SRC_PATH)/%.c,$(SRCS_LI))
A_OBJ		= $(patsubst %,$(DIR_OBJ)%.o,$(SRCS_LI))

OBJ 		= $(patsubst %,%.o,$(SRCS_LI))

LIB_DIR		= ./libft
LIB_DIR		= ./../libft
HEAD		= head.h
HEAD_DIR	= ./includes
HEAD_PATH	= $(HEAD_DIR)/$(HEAD)

LIB			= $(LIB_DIR)/libft.a

##########################
##						##
##		  DEBUG			##
##						##
##########################

VALGRIND = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=definite

##########################
##						##
##		 COLORS			##
##						##
##########################

UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
RED     = \e[31m
GREEN   = \e[32m
YELLOW  = \e[33m
BLUE	= \e[34m
MAGENTA	= \e[35m
CYAN	= \e[36m
END     = \e[0m
else
RED     = \x1b[31m
GREEN   = \x1b[32m
YELLOW  = \x1b[33m
BLUE	= \x1b[34m
MAGENTA	= \x1b[35m
CYAN	= \x1b[36m
END     = \x1b[0m
endif

COM_COLOR   = $(BLUE)
OBJ_COLOR   = $(CYAN)
OK_COLOR    = $(GREEN)
ERROR_COLOR = $(RED)
WARN_COLOR  = $(YELLOW)
NO_COLOR    = $(END)

OK_STRING    = [OK]
ERROR_STRING = [ERROR]
WARN_STRING  = [WARNING]
COM_STRING   = Compiling

MSG ?= Makefile automated push
nb ?= 10

ARG="$(MSG)"
MYST=$(shell ruby -e "puts (0..$(nb) - 1).to_a.shuffle.join(' ')")

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef

##############################################################################
##############################################################################
##																			##
##									-----									##
##									RULES									##
##									-----									##
##																			##
##############################################################################
##############################################################################

##########################
##						##
##		  BASIC			##
##						##
##########################

all :	$(NAME)

$(NAME): $(LIB) Makefile $(A_OBJ)
		@echo $(CC) $(CFLAGS) -I./$(HEAD_DIR) $(A_OBJ) $(LIB) -o $(NAME) -lm
		@$(call run_and_test, $(CC) $(CFLAGS) -I./$(HEAD_DIR) $(A_OBJ) $(LIB) -o $(NAME) -lm)

$(DIR_OBJ)%.o:$(SRC_PATH)/%.c $(HEAD_PATH)
		@$(call run_and_test, $(CC) $(CFLAGS) -o $@ -c $<)
		@echo $(CC) $(CFLAGS) -o $@ -c $<

$(LIB): FORCE
		@$(MAKE) -C $(LIB_DIR)

$(HEAD_PATH):
	@$(MAKE) -C $(LIB_DIR)

clean : libclean
		@echo "\$(YELLOW)$(NAME) objs \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@echo "\$(YELLOW)$(VISU) objs \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@rm -f $(A_OBJ)

fclean : libfclean clean
		@echo "\$(YELLOW)$(NAME) \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@echo "\$(YELLOW)$(VISU) \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"
		@rm -rf $(NAME)

libclean :
			@$(MAKE) clean -C $(LIB_DIR)

libfclean : libclean
			@$(MAKE) fclean -C $(LIB_DIR)

re :	fclean all

git :
		@git add -A
		@git status
		git commit -am "$(MSG)"
		@git push

t	:	all
		./$(NAME) $(MSG)

stat :
		@$(CC) $(CFLAGS) ./srcs/show_stats.c $(LIB) -o stats
		@./stats $(nb)

last :	all
		@./$(NAME) $(shell cat tests/last)

unit_test :
			./generator/tools/generator --big-superposition > ./maps/big_supperpo
			time ./$(NAME) maps/big_supperpo

ten :
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test
		@$(MAKE) unit_test

hund :	all
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
		@$(MAKE) ten
tho :
		@echo "0%"
		@$(MAKE) hund
		@echo "10%"
		@$(MAKE) hund
		@echo "20%"
		@$(MAKE) hund
		@echo "30%"
		@$(MAKE) hund
		@echo "40%"
		@$(MAKE) hund
		@echo "50%"
		@$(MAKE) hund
		@echo "60%"
		@$(MAKE) hund
		@echo "70%"
		@$(MAKE) hund
		@echo "80%"
		@$(MAKE) hund
		@echo "90%"
		@$(MAKE) hund
		@echo "100%"
big :
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho
		@$(MAKE) tho


vt	:	all
		@ $(VALGRIND) ./$(NAME) $(ARG)

FORCE:

##########################
##						##
##		 .PHONY			##
##						##
##########################

.PHONY : clean fclean re all git libclean libfclean t vt c vc GENERATE ten hund\
tho stat cast last FORCE
