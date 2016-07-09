/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:52:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/09 16:07:43 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_array_dict(t_dict **dicts, int dict_len)
{
	int i;

	i = 0;
	while (i < dict_len)
	{
		dict_destroy(dicts[i]);
		i++;
	}
}

int		main(int ac, char **av, char **env)
{
	t_cmd	cmd;
	t_dict	*dicts[DICT_COUNT]; /* contains all three necessary dict  env tokens binaries */

	(void)ac;
	(void)av;
	// add a functions for all init?
	init_tokens(&dicts[TOKENS]);
	// check if -1 exit?
	init_binaries(&dicts[BIN]);
	signal(SIGINT, sig_handler);
	dicts[ENV] = envcpy(env);
	interpret_command(dicts, &cmd);
	// function to destroy all dicts
	destroy_array_dict(dicts, DICT_COUNT);
	cmd_free(&cmd);
	return (0);
}
