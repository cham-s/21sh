/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 09:57:10 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/08 01:26:07 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_tokens(t_dict *tokens)
{
	tokens = dict_create();
	dict_insert(tokens, "~", "HOME");
	dict_insert(tokens, "-", "OLDPWD");
	dict_insert(tokens, "~+", "PWD");
	dict_insert(tokens, "~-", "OLDPWD");
	// printf()
	printf("%s\n", dict_search(tokens, "~"));
	return (0);
}

void	cmd_free(t_cmd *cmd)
{
	free(cmd->exepath);
}
