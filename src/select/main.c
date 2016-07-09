/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:33:33 by cattouma          #+#    #+#             */
/*   Updated: 2016/05/30 18:26:50 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	main(int ac, char **av)
{
	t_entlist	*l;

	l = ret_entlist();
	check_args(ac);
	if ((l->fd = open("/dev/tty", O_WRONLY)) < 0)
	{
		ft_putendl_fd("failed to open terminal device", 2);
		exit(EXIT_FAILURE);
	}
	init_term_data(l);
	init_raw_mode(&l->old_term);
	ft_putstr_fd(tgetstr("vi", NULL), l->fd);
	ft_putstr_fd(tgetstr("ti", NULL), l->fd);
	init_entlist(l, av, ac);
	signals();
	launcher(l);
	reset_default_mode(&l->old_term);
	print_selected(l);
	entry_destroy(l);
	return (EXIT_SUCCESS);
}
