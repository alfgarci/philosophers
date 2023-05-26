# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfgarci <alfgarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 18:06:47 by alfgarci          #+#    #+#              #
#    Updated: 2023/05/26 11:35:06 by alfgarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=\033[1;31m
GREEN	=\033[1;32m
YELLOW	=\033[1;33m
NC		=\033[0m

#---push_swap---------------------------
NAME 	=	philo
	#---SRC
SRC_DIR	=	src
SRC 	=	${SRC_DIR}/main.c \
			${SRC_DIR}/init.c \
			${SRC_DIR}/philo.c \
			${SRC_DIR}/finish.c \
			${SRC_DIR}/mutex_utils.c \
			${SRC_DIR}/checker.c \
			${SRC_DIR}/utils.c 

	#---OBJ
OBJ 	=	${SRC:.c=.o}
	#---INC
INC 	=	includes

CC			=	cc
C_FLAGS		=	-Werror -Wextra -Wall -fsanitize=thread
H_FLAGS		=	-I${INC}
FLAGS		=	${C_FLAGS}

#---RECIPES------------------------------
%.o : %.c
	@${CC} ${H_FLAGS} ${C_FLAGS} -c $< -o $@

all:	${NAME}

${NAME}: ${OBJ}
		@echo "${RED}Compiling philo...${NC}"
		@${CC} ${FLAGS} ${OBJ} -o ${NAME}
		@echo "${GREEN}${NAME} READY!${NC}"

clean:
		@rm -f ${OBJ}
		@echo "${YELLOW}OBJS REMOVED!${NC}"

fclean:		clean
		@rm -f ${NAME}
		@echo "${YELLOW}${NAME} REMOVED!${NC}"

re:		fclean all

.PHONY:	all clean fclean re
