/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 17:03:23 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 17:03:33 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	init_term_data(t_entlist *l)
{
	char	*termtype;
	int		success;
	char	*term_buffer;

	term_buffer = NULL;
	if (!isatty(l->fd))
	{
		ft_putendl_fd("Not a terminal device", 2);
		exit(EXIT_FAILURE);
	}
	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putendl_fd("Error: No TERM variable.", 2);
		exit(EXIT_FAILURE);
	}
	success = tgetent(term_buffer, termtype);
	if (success < 0)
	{
		ft_putstr_fd("The termtype ", 2);
		ft_putstr_fd(termtype, 2);
		ft_putendl_fd(" is not a valid.", 2);
		exit(EXIT_FAILURE);
	}
}
