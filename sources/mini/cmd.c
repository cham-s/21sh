/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:43:16 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/09 18:51:27 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		loop_paths(t_cmd *cmd, t_dict **dicts)
{
	int		i;
	char	*exepath;
	char	**binlist;

	binlist = ft_strsplit(dict_search(dicts[ENV], "PATH"), ':');
	i = 0;
	exepath = NULL;
	if (binlist)
	{
		while (binlist[i])
		{
			if (exepath)
				free(exepath);
			exepath = join_with_chr(binlist[i], (cmd)->av[0], '/');
			if (!access(exepath, F_OK))
			{
				cmd->exepath = ft_strdup(exepath);
				dict_insert(dicts[BIN], cmd->av[0], cmd->exepath);
				break ;
			}
			i++;
		}
		ft_delsplit(binlist);
		free(exepath);
	}
	return (0);
}

int				initcmd(t_dict **dicts, t_cmd *cmd, char **split_line)
{
	char	*bin_path;

	cmd->exepath = NULL;
	if (split_line == NULL)
		exit(EXIT_FAILURE);
	cmd->av = split_line;
	cmd->ac = ft_tablen(cmd->av);
	
	// check if the condition below is really needed
	if (cmd->av[0])
	{
		// strdup to bin_path?
		if ((bin_path = dict_search(dicts[BIN], cmd->av[0])))
		{
			cmd->exepath = ft_strdup(bin_path);
			return (0);
		}
		if (!access(cmd->av[0], F_OK))
		{
			cmd->exepath = ft_strdup(cmd->av[0]);
			dict_insert(dicts[BIN], cmd->av[0], cmd->exepath);
			return (0);
		}
		else
			return (loop_paths(cmd, dicts));
	}
	return (-1);
}
