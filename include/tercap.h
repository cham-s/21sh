/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 16:45:36 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 16:47:32 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERCAP_H
# define TERCAP_H
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include "libft.h"

# define MAX_KEY_LENGTH 5

# define K_UP		4283163
# define K_DOWN		4348699
# define K_LEFT		4479771
# define K_RIGHT	4414235
# define K_ESC		27
# define K_ENT		10
# define K_TAB		9
# define K_DEL		2117294875
# define K_BKSPC	127
# define K_SPACE	32

#endif
