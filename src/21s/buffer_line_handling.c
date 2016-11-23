#include "21sh.h"

// check if function leaks
void			edit_buffer(t_line *l, char	buf[BUFF_SIZE + 1])
{
	size_t i = l->position;
	char *end;
	char *start;
	char *start_new;
	/* size_t tmp = l->position; */
	while (i--)
	{
		ft_putstr(tgetstr("le", NULL));
		ft_putstr(tgetstr("dc", NULL));
	}
	end = ft_strdup(l->buffer + l->position);
	start = ft_strsub(l->buffer, 0, l->position);
	start_new = ft_strjoinfree(start, buf);
	l->buffer = ft_strjoinfree(start_new, end);
	l->end = ft_strlen(l->buffer);
	ft_putstr(l->buffer);
	i = ft_strlen(l->buffer) - (l->position + 1);
	++l->position;
	while (i--)
		ft_putstr(tgetstr("le", NULL));
}

void			handle_special_keys(t_line *l, t_hcontrol *c)
{
	if (l->key == K_UP)
		backward_history(l, c);
	else if (l->key == K_DOWN)
		foreward_history(l, c);
	else if (l->key == K_LEFT && l->position > 0)
		move_left(l);
	else if (l->key == K_RIGHT && l->buffer[l->position])
		move_right(l);
	else if (l->key == K_ALT_L && l->position > 0)
		move_word_left(l);
	else if (l->key == K_ALT_R && l->buffer[l->position])
		move_word_right(l);
	else if (l->key == K_BKSPC && l->position > 0)
		erase_back(l);
	else if (l->key == K_HOME)
		go_home_of_line(l);
	else if (l->key == K_END)
		go_end_of_line(l);
	else if (l->key == K_ALT_DOWN)
		go_end_of_line(l);
}
