# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:14:53 by asid-ahm          #+#    #+#              #
#    Updated: 2024/06/03 08:41:36 by asid-ahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN_B = "\033[1;32m"
RED_BI = "\033[1;3;31m"
BLUE_I = "\033[3;34m"
YELLOW = "\033[0;33m"
RESET = "\033[0m"

CC = cc
CFLAGS = -Wall -Werror -Wextra -I.

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = SRC
OBJDIR = OBJ
NAME = pipex
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME_BONUS = pipex_bonus
BSDIR = BSRC
BODIR = BOBJ
BSOURCE = $(shell find $(BSDIR) -type f -name '*.c')
BOBJECT = $(BSOURCE:$(BSDIR)/%.c=$(BODIR)/%.o)

all: $(NAME)
	@-echo $(GREEN_B)"\n$(NAME) is Compiled.🐢 \n"$(RESET)

$(NAME): $(OBJECTS) $(LIBFT)
	@-$(CC) $(OBJECTS) -o $(NAME) -L$(LIBFT_DIR) -lft 

$(LIBFT):
	@-make -C $(LIBFT_DIR)
	@-echo $(YELLOW)".\c"$(RESET)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@-mkdir -p $(OBJDIR)
	@-$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)
	@-echo $(BLUE_I)"\n$(NAME_BONUS) is Compiled.🍀 \n"$(RESET)

$(NAME_BONUS): $(BOBJECT) $(LIBFT)
	@-$(CC) $(BOBJECT) -o $(NAME_BONUS) -L$(LIBFT_DIR) -lft 

$(BODIR)/%.o: $(BSDIR)/%.c
	@-mkdir -p $(BODIR)
	@-$(CC) $(CFLAGS) -c $< -o $@
	@-echo $(YELLOW)".\c"$(RESET)

clean:
	@-rm -rf $(OBJDIR) $(BODIR)
	@-make -C $(LIBFT_DIR) clean
	@-echo $(YELLOW)"Cleaned"$(RESET)

	
fclean: clean
	@-rm -rf $(NAME) $(NAME_BONUS)
	@-make -C $(LIBFT_DIR) fclean
	@-echo $(YELLOW)"Fully cleaned"$(RESET)

re: fclean all

.PHONY: all bonus clean fclean re
