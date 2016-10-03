/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:33:39 by cattouma          #+#    #+#             */
/*   Updated: 2016/10/03 21:51:24 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"
# include "dict.h"

# define MAX_KEY_LENGTH 5
# define BUFF_SIZE	5
# define START 6

# define K_UP		4283163
# define K_DOWN		4348699
# define K_LEFT		4479771
# define K_RIGHT	4414235
# define K_HOME		4741915
# define K_END		4610843
# define K_ALT_R  	1130044187
# define K_ALT_L    1146821403
# define K_ALT_DOWN	1113266971
# define K_ALT_UP	1096489755
# define K_ESC		27
# define K_ENT		10
# define K_TAB		9
# define K_DEL		2117294875
# define K_BKSPC	127
# define K_SPACE	32
# define K_A		'a'
# define K_R		'r'
# define K_D		'd'
# define K_X		'x'

# define SPACE		3
# define PAD		4

# define X			1
# define R			2
# define D			3

# define D_MENU_L	170

# define MAX_SIGNAL 32

typedef struct		s_file
{
	int				fd;
	char			*buffer;
	struct s_file	*right;
	struct s_file	*left;
}					t_file;

typedef struct		s_line
{
	char			*line;
	char			*buffer;
	char			*tmp;
	size_t			position;
	size_t			start;
	size_t			end;
	size_t			size;
	unsigned int	key;
	int				term_height;
	int				term_width;
	int				level;
	int				level_count;
	struct termios	old_term;
}					t_line;

typedef struct		s_entry
{
	char			*line;
	int				hl;
	int				us;
	int				t;
	struct s_entry	*next;
	struct s_entry	*prev;
}					t_entry;

typedef struct		s_line_stack
{
	char			*str;
	int				size;
	int				index;
	int				h_index;
	char			**array;
}					t_line_stack;

typedef	struct		s_entlist
{
	t_entry			*head;
	t_entry			*list;
	int				fd;
	int				height;
	int				width;
	int				row;
	int				col;
	int				col_max;
	int				ac;
	int				max_len;
	int				sel_v;
	int				i;
	int				j;
	int				times;
	struct termios	old_term;
}					t_entlist;

/*ft_select */

t_line				*ret_line(void);
void				sig_handler(int sig);
void				signals(void);
void				init_raw_mode(struct termios *old);
void				reset_default_mode(struct termios *old);
void				init_term_data(int fd);
void				entry_destroy(t_entlist *l);
void				getargs(int ac, char **av, t_entlist *l);
void				addentry(t_entlist *list, t_entry *new);
void				init_entlist(t_entlist *l, char **av, int ac);
t_entry				*newentry(char *str);
int					launcher(t_entlist *l);
void				draw(t_entlist *l);
void				set_draw(t_entlist *l);
void				print_selected(t_entlist *l);
int					delete_entry(t_entlist *l);
void				quit(t_entlist *l);
int					check_window_size(t_entlist *l);
int					nbr_col(t_entlist *l);
void				clean_screen(t_entlist *l);
void				select_all(t_entlist *l, int value);
void				print_entry_color(t_entlist *l, t_entry *e);
void				check_args(int ac);
void				go_down(t_entlist *l);
void				go_up(t_entlist *l);
void				go_left(t_entlist *l);
void				go_right(t_entlist *l);
void				delete_key(t_entlist *l);
void				key_handler(unsigned int key, t_entlist *l, int *running);
void				select_specific(t_entlist *l, int value, int v);
void				draw_title(t_entlist *l);
void				draw_help(t_entlist *l);

void				init_line(t_line *l, t_dict *env);

/*
 * stack implementation
 */
t_line_stack		*stack_create(void);
t_line_stack		*init_stack(int size);
void				stack_destroy(t_line_stack *stack);
void				stack_grow(t_line_stack *stack, int growth_factor, int index);
void				push_stack(t_line_stack *stack, char *line);

#endif
