/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:24:07 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 17:55:55 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void			env_usage(char c)
{
	ft_putstr_fd("env: illegal options : -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd("Usage: env [-i] [command]", 2);
}

static int			check_options(int ac, char **av, int *f, int *start)
{
	int		i;
	int		j;

	i = 0;
	i++;
	while (ac-- > 1 && av[i][0] == '-' && av[i][1] != '\0')
	{
		j = 1;
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		while (av[i][j])
		{
			if (av[i][j] != 'i')
			{
				(*start)++;
				env_usage(av[i][j]);
				return (-1);
			}
			*f = 1;
			j++;
		}
		(*start)++;
		i++;
	}
	return (0);
}

static void			st_exec(t_cmd *tcmd, t_dict **dicts, int *f)
{
	char	**env_tab;

	env_tab = dict_to_tab(dicts[ENV]);
	if (!*f)
		launch_exec(tcmd, dicts, env_tab);
	else
		launch_exec(tcmd, dicts, NULL);
	ft_delsplit(env_tab);
}

int					start_env(t_dict **dicts, t_cmd *cmd, char **env)
{
	t_cmd	tcmd;
	char	**s_line;
	int		f;
	int		start;

	free(cmd->exepath);
	f = 0;
	start = 0;
	if (cmd->ac == 1)
	{
		//ft_putenv(dicts[ENV]);
		print_env(env);
		return (1);
	}
	if (check_options(cmd->ac, cmd->av, &f, &start) == -1)
		return (1);
	s_line = NULL;
	if (!f)
		s_line = cmd->av + 1;
	else
		s_line = cmd->av + start + (f ? 1 : 0);
	if (initcmd(dicts, &tcmd, s_line) != -1)
		st_exec(&tcmd, dicts, &f);
	return (1);
}
