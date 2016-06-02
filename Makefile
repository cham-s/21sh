# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/02 16:30:48 by cattouma          #+#    #+#              #
#    Updated: 2016/06/02 16:42:16 by cattouma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 21sh 
CC 			= clang
LIB 		= libft/libft.a
FLAGS 		= -Wall -Werror -Wextra
INCLUDES 	= -I include -I libft/includes
INC			= include/minishell.h include/cd.h include/dict.h
OBJDIR		= obj
OBJS 		= $(OBJDIR)/main.o\
			  $(OBJDIR)/utils.o\
			  $(OBJDIR)/exec.o\
			  $(OBJDIR)/env.o\
			  $(OBJDIR)/cmd.o\
			  $(OBJDIR)/dictionary.o\
			  $(OBJDIR)/dictionary2.o\
			  $(OBJDIR)/split_parse.o \
			  $(OBJDIR)/error.o\
			  $(OBJDIR)/parser.o\
			  $(OBJDIR)/init.o\
			  $(OBJDIR)/cd_initopt.o\
			  $(OBJDIR)/cd_parser.o\
			  $(OBJDIR)/cd.o\
			  $(OBJDIR)/builtins.o\
			  $(OBJDIR)/builtins2.o

.PHONY: all clean fclean re

VPATH = src/mini:src/cd:src/dict

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIB) -o $(NAME) -ltermcap

$(LIB):
	make -C libft/

$(OBJDIR)/%.o : %.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all
