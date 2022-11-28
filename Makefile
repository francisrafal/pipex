# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frafal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 10:02:44 by frafal            #+#    #+#              #
#    Updated: 2022/11/28 16:51:47 by frafal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= pipex
CC				:= cc
RM		    	:= rm -f
FLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g

HEADDIR			:= ./includes/
HEADLIST		:= pipex.h
HEADERS			:= $(addprefix ${HEADDIR}, ${HEADLIST})

SRCSDIR			:= ./src/
SRCSLIST		:= main.c
SRCS			:= $(addprefix ${SRCSDIR}, ${SRCSLIST})

OBJSDIR			:= ./obj/
OBJSLIST		:= ${SRCSLIST:.c=.o}
OBJS			:= $(addprefix ${OBJSDIR}, ${OBJSLIST})

LIBFTDIR		:= ./libft/
LIBFT			:= ${LIBFTDIR}libft.a

LIBS			:= -L${LIBFTDIR} -lft 
INCS			:= -I${HEADDIR} -I${LIBFTDIR} 

CYAN			:= \033[0;36m
RESET			:= \033[0m

${NAME}:		${LIBFT} ${OBJSDIR} ${OBJS}
				@echo ""
				@echo "${CYAN}Compiling ${NAME} ...${RESET}"
				${CC} ${FLAGS} ${DEBUG} ${OBJS} -o ${NAME} ${LIBS} ${INCS}
				@echo ""
				@echo "${CYAN}$(NAME) Created${RESET}"

${LIBFT}:
				make -C ${LIBFTDIR}

${OBJSDIR}%.o:	${SRCSDIR}%.c ${HEADERS} compiling
				${CC} ${FLAGS} ${DEBUG} ${INCS} -c $< -o $@

${OBJSDIR}:
				mkdir -p ${OBJSDIR}

.PHONY:			all clean fclean re test 

.INTERMEDIATE:	compiling

compiling:
				@echo ""
				@echo "${CYAN}Compiling Objects ...${RESET}"

all:			${NAME}

clean:
				@echo ""
				@echo "${CYAN}Deleting $(NAME) Objects ...${RESET}"
				${RM} -r ${OBJSDIR}
				make -C ${LIBFTDIR} clean

fclean:			clean
				@echo ""
				@echo "${CYAN}Deleting $(NAME) Executable ...${RESET}"
				${RM} ${NAME}
				make -C ${LIBFTDIR} fclean

re:				fclean all

test:			all
				./${NAME} infile "ls -l" "wc-l" outfile 
				./${NAME} infile "grep a1" "wc-w" outfile 
