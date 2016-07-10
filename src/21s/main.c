/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:52:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/09 18:54:40 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

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
	t_dict	*dicts[DICT_COUNT];

	(void)ac;
	(void)av;
	init_tokens(&dicts[TOKENS]);
	init_binaries(&dicts[BIN]);
	dicts[ENV] = envcpy(env);
	signal(SIGINT, sig_handler);
	interpret_command(dicts, &cmd);
	destroy_array_dict(dicts, DICT_COUNT);
	cmd_free(&cmd);
	return (0);
}