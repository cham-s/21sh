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

char	*g_prog_name;

int		main(int ac, char **av, char **env)
{
	t_cmd	cmd;
	t_dict	*dicts[3]; /* contains all three necessary dict  env tokens binaries */

	(void)ac;
	(void)av;
	init_tokens(&dicts[TOKENS]);
	//
	signal(SIGINT, sig_handler);
	dicts[ENV] = envcpy(env);
	interpret_command(dicts, &cmd);
	cmd_free(&cmd);
	return (0);
}
