/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 16:44:17 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/02 16:44:46 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cd.h"

t_cdflag		g_options;

int				ft_cd(int ac, char **av, t_dict *env)
{
	char *directory;
	char *oldpwd;
	char *pwd;
	char buff[PATH_MAX + 1];

	directory = NULL;
	initoptions(&g_options);
	getoptions(ac, av);
	if (getdir(ac, av, env, &directory) == 0)
	{
		oldpwd = getcwd(buff, PATH_MAX + 1);
		if (chdir(directory) < 0)
		{
			free(directory);
			return (-1);
		}
		ft_setenv("OLDPWD", (!oldpwd ? NULL : oldpwd), env, 1);
		pwd = getcwd(buff, PATH_MAX + 1);
		ft_setenv("PWD", (!pwd ? NULL : pwd), env, 1);
		free(directory);
		return (0);
	}
	return (-1);
}

static void		check_opts(char *str, int *flair)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (OPTIN(CD_OPT, str[i]) == NULL)
		{
			*flair = 1;
			break ;
		}
		else
		{
			if (str[i] == 'P' && !g_options.p)
				g_options.p = 1;
			else if (str[i] == 'L' && !g_options.l)
				g_options.l = 1;
		}
		i++;
	}
}

void			getoptions(int ac, char **av)
{
	int		i;
	int		flair;

	flair = 0;
	i = 0;
	i++;
	while (ac-- > 1 && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		check_opts(av[i], &flair);
		if (flair)
			break ;
		i++;
	}
}

int				check_solo_arg(t_dict *env, char **buffer)
{
	char *home;

	home = dict_search(env, "HOME");
	if (!home)
	{
		env_missing("HOME");
		return (-1);
	}
	*buffer = ft_strdup(home);
	return (0);
}

int				add_to_buff(int ac, char **av, int *i, char ***buffer)
{
	if (ac > 3)
	{
		ft_putendl_fd("cd : too many arguments", 2);
		return (-1);
	}
	if (!av[*i + 1])
	{
		if (check_dir(av[*i]) != -1)
			**buffer = ft_strdup((av[*i]));
	}
	else
	if (check_dir(av[*i + 1]) != -1)
		**buffer = ft_strdup(av[*i + 1]);
	return (0);
}
