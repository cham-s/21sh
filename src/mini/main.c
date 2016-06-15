/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/15 09:16:35 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/15 09:17:02 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_dict	*g_tokens;
char	*g_prog_name;

int		main(int ac, char **av, char **env)
{
	t_cmd	cmd;
	t_dict	*envc;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	envc = envcpy(env);
	init_tokens();
	interpret_command(envc, &cmd);
	dict_destroy(g_tokens);
	dict_destroy(envc);
	cmd_free(&cmd);
	return (0);
}
