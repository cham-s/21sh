/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:57:10 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/09 15:28:07 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	init_line(t_line *l, t_dict *env)
{
	l->line = NULL;
	l->buffer = ft_strdup("");
	l->tmp = NULL;
	l->position = 0;
	l->size = 0;
	l->key = 0;
	l->start = ft_strlen(dict_search(env, "PWD") + 3); // + '$> '
	l->end = l->start;
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
