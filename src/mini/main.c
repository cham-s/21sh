/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 09:16:35 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/15 10:28:14 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*g_prog_name;

int		main(int ac, char **av, char **env)
{
	t_cmd	cmd;
	t_dict	*envc;
	t_dict	*dicts[DICT_COUNT]; /* contains all three necessary dict */

	(void)ac;
	(void)av;
	dicts[ENV] = NULL;
	dicts[TOKENS] = NULL;
	dicts[BIN] = NULL;
	signal(SIGINT, sig_handler);
	envc = envcpy(env);
	init_tokens(dicts[TOKENS]);
	interpret_command(envc, &cmd, dicts);
	dict_destroy(dicts[TOKENS]);
	dict_destroy(envc);
	cmd_free(&cmd);
	return (0);
}
