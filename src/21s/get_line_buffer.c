#include "21sh.h"

static int		is_special_key(unsigned int key)
{
	if (key == K_UP || key == K_DOWN || key == K_LEFT || key == K_RIGHT ||
		key == K_ESC || key == K_ENT || key == K_DEL || key == K_BKSPC ||
		key == K_TAB || key == K_ALT_L || key == K_ALT_R || key == K_HOME ||
	   	key == K_END || key == K_ALT_DOWN || key == K_ALT_UP || key == K_SPE_UP || key == K_SPE_DOWN)
		return 1;
	return 0;
}

void			display_buffer(t_line *l, char	buf[BUFF_SIZE + 1])
{
	l->buffer = ft_strjoinfree(l->buffer, buf);
	++l->size;
	++l->position;
	++l->end;
	ft_putstr(buf);
	if (l->level_count == 1)
	{
		if(l->level_bucket == (l->term_width - PROMPT_SIZE - 1))
		{
			ft_putchar('\n');
			l->level_bucket = 0;
			++l->level_count;
		}
	}
	else
	{
		if (l->level_bucket == (l->term_width))
		{
			ft_putchar('\n');
			l->level_bucket = 0;
			++l->level_count;
		}
	}
	++l->level_bucket;
}

void		update_line_level(t_line *l, int back)
{
	(void)back;
	double	result;
	int		trunc;
	size_t	size;

	size = ft_strlen(l->buffer);
	if (((int)size + 6) < l->term_width)
	{
		l->level_count = 1;
		return ;
	}
	result = ((double)size + 6) / (double)l->term_width;
	trunc = (size + 6) / l->term_width;
	if ((double)trunc < result)
		l->level_count = trunc + 1;  /* It means there is part of the next level */
	else
		l->level_count = trunc; 
}

void		move_cursor_down(t_line *l)
{
	int i =  l->term_width + 6;
	while (i--)
	{
		++l->position;
		ft_putstr(tgetstr("nd", NULL));
	}
}

// if potential leaks probably here
static int		getline2(char **line, int fd, t_dict *env, t_hcontrol *c)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	int				is_running;
	t_line			*l;

	is_running = 1;
	ret = BUFF_SIZE;
	l = ret_line();
	init_line(l, env);
	while (is_running && ret)
	{
		ft_bzero(buf, MAX_KEY_LENGTH);
		if ((ret = read(fd, buf, MAX_KEY_LENGTH)) < 0)
			return (-1);
		l->key = *(unsigned int *)buf;
		//ft_putnbr(l->key);
		if (is_special_key(l->key))
		{
			// handle special key with termcap
			if (l->key == K_ENT)
			{
				l->level_count = 1;
				is_running = 0;
			}
			else
				handle_special_keys(l, c);
		}
		else
		{
			buf[ret] = '\0';
			if (l->buffer[l->position])
				edit_buffer(l, buf);
			else
				display_buffer(l, buf);
		}
	}
	ft_putendl("");
	*line = ft_strdup(l->buffer);
	if (l->buffer[0])
		add_history(c, new_history(l->buffer));
	// reset history
	c->list = c->head;
	c->passage = 0;
	l->tmp = l->buffer;
	ft_strdel(&l->tmp);
	if (ret == 0 && *line[0] == '\0')
		return (0);
	return (1);
}

int				get_line_buffer(int const fd, char **line, t_dict *env, t_hcontrol *c)
{
	int				res;

	if (fd < 0 || !line)
		return (-1);
	else
	{
		init_term_data(fd);
		init_raw_mode(&c->old_term);
		res = getline2(line, fd, env, c);
		reset_default_mode(&c->old_term);
		return (res);
	}
}
