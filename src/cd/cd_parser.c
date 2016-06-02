/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:59:55 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/21 17:04:34 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static void		chk(char *str, int *ac, int *i, int *flair)
{
	int j;

	j = 1;
	while (str[j])
	{
		if (OPTIN(CD_OPT, str[j]) == NULL)
		{
			(*ac) += 1;
			(*i) -= 1;
			*flair = 1;
			break ;
		}
		j++;
	}
}

int				getdir(int ac, char **av, t_dict *env, char **buffer)
{
	int		i;
	int		flair;

	flair = 0;
	i = 0;
	i++;
	if (!av[i])
		return (check_solo_arg(env, buffer));
	while (ac-- > 1 && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (ft_strcmp(av[i], "--") == 0)
			break ;
		chk(av[i], &ac, &i, &flair);
		if (flair)
			break ;
		i++;
	}
	return (add_to_buff(ac, av, &i, &buffer));
}

int				check_dir(char *dir)
{
	char		*message;
	struct stat	file;

	if (!ft_strcmp(dir, "~") || !ft_strcmp(dir, "-"))
		return (0);
	message = NULL;
	if (stat(dir, &file) < 0)
		message = "No such file or directory: ";
	else if (access(dir, X_OK))
		message = "Permission denied: ";
	else if (!S_ISDIR(file.st_mode))
		message = "Not a directory: ";
	if (!message)
		return (0);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(message, 2);
		ft_putendl_fd(dir, 2);
		return (-1);
	}
}
