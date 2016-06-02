/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:57:10 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/16 09:05:06 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_tokens(void)
{
	g_tokens = dict_create();
	if (!g_tokens)
		return (-1);
	dict_insert(g_tokens, "~", "HOME");
	dict_insert(g_tokens, "-", "OLDPWD");
	dict_insert(g_tokens, "~+", "PWD");
	dict_insert(g_tokens, "~-", "OLDPWD");
	return (0);
}

void	cmd_free(t_cmd *cmd)
{
	free(cmd->exepath);
}
