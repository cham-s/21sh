/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 19:19:26 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 19:52:57 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "cd.h"

void	print_echo(char **av)
{
	int i;

	i = 0;

	if (av == NULL)
		ft_putchar('\n');
	else
	{
		while (av[i])
		{
			if (i != 0)
				ft_putchar('+');
			ft_putstr(av[i]);
			i++;
		}
	}
	ft_putchar('\n');
}

int		start_echo(t_dict *env, t_cmd *cmd)
{
	char **av_tab;

	(void)env;
	av_tab = (cmd->av) + 1;
	print_echo(av_tab);
	//
	return (1);
}
