/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:32:41 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/15 09:16:27 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "cd.h"

static int		check_bltn(t_cmd *cmd, t_dict *dictenv)
{
	int is_blt;

	is_blt = 0;
	if (cmd->ac > 0)
	{
		if (!ft_strcmp(cmd->av[0], "env"))
			is_blt = start_env(dictenv, cmd);
		else if (!ft_strcmp(cmd->av[0], "setenv"))
			is_blt = start_setenv(dictenv, cmd);
		else if (!ft_strcmp(cmd->av[0], "unsetenv"))
			is_blt = start_unsetenv(dictenv, cmd);
		else if (!ft_strcmp(cmd->av[0], "cd"))
			is_blt = start_cd(dictenv, cmd);
		else if (!ft_strcmp(cmd->av[0], "exit"))
			is_blt = start_exit(dictenv, cmd);
		if (is_blt)
			return (1);
	}
	return (0);
}

void			launch_exec(t_cmd *cmd, t_dict *dictenv, char **env)
{
	pid_t	child_pid;
	pid_t	t_pid;
	int		status;

	t_pid = 0;
	if (!dictenv)
		return ;
	if (check_bltn(cmd, dictenv))
		return ;
	child_pid = fork();
	if (child_pid == 0)
	{
		execve(cmd->exepath, cmd->av, env);
		if (!dict_search(dictenv, "PATH"))
			env_missing("PATH");
		else
			put_error(cmd->exepath, cmd->av[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(t_pid, &status, 0);
		cmd_free(cmd);
		return ;
	}
}

void			display_prompt(t_dict *dictenv)
{
	char *prompt;

	prompt = dict_search(dictenv, "PWD");
	prompt = (dict_search(dictenv, "PWD") ? prompt : "minishell");
	ft_putstr("\x1B[33m");
	ft_putstr(prompt);
	ft_putstr("$> ");
	ft_putstr("\033[0m");
}

void			interpret_command(t_dict *dictenv, t_cmd *cmd)
{
	char	*line;
	char	**big_line;
	char	**split_line;
	char	**env;
	int		i;

	i = 0;
	while (1)
	{
		display_prompt(dictenv);
		if (get_next_line(0, &line) == 0)
			exit(0);
		env = dict_to_tab(dictenv);
		big_line = ft_strsplit(line, ';');
		i = 0;
		while (big_line[i])
		{
			split_line = split_parse(big_line[i], dictenv);
			if (initcmd(dictenv, cmd, split_line) != -1)
				launch_exec(cmd, dictenv, env);
			ft_delsplit(split_line);
			i++;
		}
		clean_malloc(line, big_line, env);
	}
}
