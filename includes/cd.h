/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:34:27 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/21 17:01:39 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H
# include <sys/stat.h>
# include "minishell.h"
# include "dict.h"
# define CD_OPT			"LP"
# define OPTIN(a, b)	ft_strchr(a, b)
# define NOTPWD			1
# define PATH_MAX		4096

typedef	struct	s_cdflag
{
	int		l;
	int		p;
}				t_cdflag;

extern	t_cdflag g_options;

void			getoptions(int ac, char **av);
int				getdir(int ac, char **av, t_dict *env, char **buffer);
int				ft_cd(int ac, char **av, t_dict *env);
void			initoptions(t_cdflag *options);
int				check_dir(char *dir);
void			getoptions(int ac, char **av);
int				check_solo_arg(t_dict *env, char **buffer);
int				add_to_buff(int ac, char **av, int *i, char ***buffer);

#endif
