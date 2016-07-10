/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:20:16 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/16 08:35:18 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "cd.h"

int		start_unsetenv(t_dict *env, t_cmd *cmd)
{
	free(cmd->exepath);
	ft_unsetenv(cmd->av[1], env);
	return (1);
}

int		start_setenv(t_dict *env, t_cmd *cmd)
{
	free(cmd->exepath);
	if (cmd->ac == 1)
		ft_putendl_fd("setenv: too few arguments", 2);
	else if (cmd->ac > 4)
		ft_putendl_fd("setenv: too many arguments", 2);
	else
	{
		if (cmd->ac == 2)
			ft_setenv(cmd->av[1], "", env, 1);
		else if (cmd->ac == 4)
			ft_setenv(cmd->av[1], cmd->av[2], env, ft_atoi(cmd->av[3]));
		else
			ft_setenv(cmd->av[1], cmd->av[2], env, 0);
	}
	return (1);
}

int		start_exit(t_dict *env, t_cmd *cmd)
{
	(void)env;
	free(cmd->exepath);
	if (cmd->ac > 2)
		ft_putendl_fd("exit: too many arguments", 2);
	else
	{
		ft_putendl("exit");
		if (cmd->ac == 1)
			exit(0);
		else
		{
			if (is_numeric(cmd->av[1]))
				exit(ft_atoi(cmd->av[1]));
			else
			{
				ft_putstr_fd("21sh: ", 2);
				ft_putstr_fd(cmd->av[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(-1);
			}
		}
	}
	return (1);
}

int		start_cd(t_dict *env, t_cmd *cmd)
{
	free(cmd->exepath);
	ft_cd(cmd->ac, cmd->av, env);
	return (1);
}
