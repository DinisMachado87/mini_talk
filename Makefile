# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimachad <dimachad@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 15:08:24 by dimachad          #+#    #+#              #
#    Updated: 2025/05/13 22:16:46 by dimachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimachad <dimachad@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 15:08:24 by dimachad          #+#    #+#              #
#    Updated: 2025/05/12 23:22:11 by dimachad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME_CLIENT  = client
NAME_SERVER  = server
CC          = cc
RM          = rm -f
FLAGS       = -Wall -Werror -Wextra
DEBUG_FLAGS = -Wall -Werror -Wextra -g -O0
LIBFTDIR    = libft/

# Sources and objects
SRC_CLIENT  = client.c
SRC_SERVER  = server.c
OBJ_CLIENT  = ${SRC_CLIENT:.c=.o}
OBJ_SERVER  = ${SRC_SERVER:.c=.o}
INCLUDE     = -L ./libft -lft

# Default target: Build the minitalk client and server
all: ${NAME_CLIENT} ${NAME_SERVER}

# Build client executable
${NAME_CLIENT}: ${OBJ_CLIENT}
	make -C $(LIBFTDIR)  # Build the libft library
	${CC} ${FLAGS} ${OBJ_CLIENT} -o ${NAME_CLIENT} ${INCLUDE}

# Build server executable
${NAME_SERVER}: ${OBJ_SERVER}
	make -C $(LIBFTDIR)  # Build the libft library
	${CC} ${FLAGS} ${OBJ_SERVER} -o ${NAME_SERVER} ${INCLUDE}

# Debug target: Build with debug flags
debug: ${NAME_CLIENT}_debug ${NAME_SERVER}_debug

${NAME_CLIENT}_debug: ${SRC_CLIENT}
	make -C $(LIBFTDIR)  # Build the libft library
	${CC} ${DEBUG_FLAGS} ${SRC_CLIENT} -o ${NAME_CLIENT}_debug ${INCLUDE}

${NAME_SERVER}_debug: ${SRC_SERVER}
	make -C $(LIBFTDIR)  # Build the libft library
	${CC} ${DEBUG_FLAGS} ${SRC_SERVER} -o ${NAME_SERVER}_debug ${INCLUDE}

# Compile .c files into .o files
.c.o:
	${CC} ${FLAGS} -c $< -o $@

# Clean up object files and executables
clean:
	${RM} ${OBJ_CLIENT} ${OBJ_SERVER}
	cd $(LIBFTDIR) && $(MAKE) clean

# Full clean (also remove the executables)
fclean: clean
	${RM} ${NAME_CLIENT} ${NAME_SERVER} ${NAME_CLIENT}_debug ${NAME_SERVER}_debug
	cd $(LIBFTDIR) && $(MAKE) fclean

# Rebuild everything
re: fclean all

# .PHONY to avoid conflicts with file names
.PHONY: all clean fclean re debug
