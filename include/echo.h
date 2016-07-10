/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 19:07:14 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 19:33:23 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H
# include <sys/stat.h>
# include "21sh.h"
# include "dict.h"
# define ECHO_OPT		"neE"

typedef	struct	s_echoflag
{
	int		n;
	int		e;
	int		g_e;
}				t_echoflag;

extern	t_echoflag g_echo_options;

#endif
