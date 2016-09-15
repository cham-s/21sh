/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:57:10 by cattouma          #+#    #+#             */
/*   Updated: 2016/09/15 15:42:57 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line	*ret_line(void)
{
	static t_line l;

	return (&l);
}

void	init_line(t_line *l, t_dict *env)
{
	struct winsize	w;

	//use env?
	if (ioctl(1, TIOCGWINSZ, &w) < 0)
	{
		ft_putendl_fd("error using ioctl()", 2);
		exit(EXIT_FAILURE);
	}
	l->term_height = w.ws_row;
	l->term_width = w.ws_col;
	(void)env;
	l->line = NULL;
	l->buffer = ft_strdup("");
	l->tmp = NULL;
	l->size = 0;
	l->key = 0;
	l->start = ft_strlen("21sh> "); // + '$> '
	l->end = l->start;
	l->position = 0;
}

int		init_binaries(t_dict **binaries)
{
	*binaries = dict_create();
	if (*binaries == NULL)
		return (-1);
	return (0);
}

int		init_tokens(t_dict **tokens)
{
	*tokens = dict_create();
	dict_insert(*tokens, "~", "HOME");
	dict_insert(*tokens, "-", "OLDPWD");
	dict_insert(*tokens, "~+", "PWD");
	dict_insert(*tokens, "~-", "OLDPWD");
	return (0);
}

void	cmd_free(t_cmd *cmd)
{
	free(cmd->exepath);
}
