/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:32:41 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 19:34:54 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "cd.h"

static int		check_bltn(t_cmd *cmd, t_dict **dicts, char **env)
{
	int is_blt;

	is_blt = 0;
	if (cmd->ac > 0)
	{
		if (!ft_strcmp(cmd->av[0], "env"))
			is_blt = start_env(dicts, cmd, env);
		else if (!ft_strcmp(cmd->av[0], "setenv"))
			is_blt = start_setenv(dicts[ENV], cmd);
		else if (!ft_strcmp(cmd->av[0], "unsetenv"))
			is_blt = start_unsetenv(dicts[ENV], cmd);
		else if (!ft_strcmp(cmd->av[0], "cd"))
			is_blt = start_cd(dicts[ENV], cmd);
		else if (!ft_strcmp(cmd->av[0], "exit"))
			is_blt = start_exit(dicts[ENV], cmd);
		else if (!ft_strcmp(cmd->av[0], "echo"))
			is_blt = start_echo(dicts[ENV], cmd);
		if (is_blt)
			return (1);
	}
	return (0);
}

void			launch_exec(t_cmd *cmd, t_dict **dicts, char **env)
{
	pid_t	pid;
	pid_t	t_pid;
	int		status;

	t_pid = 0;
	if (!dicts[ENV])
		return ;
	if (check_bltn(cmd, dicts, env))
		return ;
	pid = fork();
	if (pid < 0)
	{
		// error 
		ft_putendl_fd("Error failed to fork()", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(t_pid, &status, 0);
		cmd_free(cmd);
		return ;
	}
	else
	{
		execve(cmd->exepath, cmd->av, env);
		if (!dict_search(dicts[ENV], "PATH"))
			env_missing("PATH");
		else
			put_error(cmd->exepath, cmd->av[0]);
		_exit(EXIT_FAILURE);
	}
}

void			display_prompt(t_dict *dictenv)
{
	//use env?
	/* char *prompt; */

	(void)dictenv;
	/* prompt = dict_search(dictenv, "PWD"); */
	/* prompt = (dict_search(dictenv, "PWD") ? prompt : "21sh"); */
	ft_putstr("\x1B[33m");
	/* ft_putstr(prompt); */
	ft_putstr("21sh> ");
	ft_putstr("\033[0m");
}

void			interpret_command(t_dict **dicts, t_cmd *cmd)
{
	t_line_info	li;
	char		**env;
	int			i;

	while (1)
	{
		display_prompt(dicts[ENV]);
		if (get_line_buffer(0, &li.line, dicts[ENV]) == 0)
			exit(EXIT_FAILURE);
		env = dict_to_tab(dicts[ENV]); /* transform env dict into tab */
		li.big_line = ft_strsplit(li.line, ';');
		i = 0;
		while (li.big_line[i])
		{
			li.split_line = split_parse(li.big_line[i], dicts);
			if (initcmd(dicts, cmd, li.split_line) != -1)
				launch_exec(cmd, dicts, env);
			ft_delsplit(li.split_line);
			i++;
		}
		clean_malloc(li.line, li.big_line, env);
	}
}
