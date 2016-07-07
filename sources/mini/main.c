/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:52:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/08 01:28:05 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
#include <stdio.h>

t_dict	*g_tokens;
char	*g_prog_name;

int		main(int ac, char **av, char **env)
{
	t_cmd	cmd;
	t_dict	*envc;
	t_dict	**dicts; /* contains all three necessary dict */

	dicts = (t_dict **)malloc(sizeof(t_dict) * DICT_COUNT);
	dicts[ENV] = NULL;
	dicts[TOKENS] = NULL;
	dicts[BIN] = NULL;
	(void)ac;
	(void)av;
	init_tokens(dicts[TOKENS]);
	//
	exit(3);
	signal(SIGINT, sig_handler);
	envc = envcpy(env);
	init_tokens(dicts[TOKENS]);
	interpret_command(envc, &cmd, dicts);
	dict_destroy(dicts[TOKENS]);
	dict_destroy(envc);
	cmd_free(&cmd);
	return (0);
}
