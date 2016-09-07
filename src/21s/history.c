#include "21sh.h"

t_history	*newentry(char *str)
{
	t_history *new;

	new = (t_entry *)ft_memalloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->line = ft_strdup(str);
	return (new);
}

void	init_history(t_hcontrol *c)
{
	c->head = NULL;
	c->list = NULL;
	c->max = 0;
}

void	add_history(t_hcontrol *c, t_history *new)
{
	t_history		*tmp;
	t_history		*slow;

	tmp = c->list;
	if (!tmp)
		c->list = new;
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		++c->max;
	}
}

/* void	entry_destroy(t_hcontrol *c) */
/* { */
/* 	t_entry *tmp; */
/* 	int		i; */
/*  */
/* 	i = 0; */
/* 	if (l->head) */
/* 	{ */
/* 		while (i < l->ac) */
/* 		{ */
/* 			tmp = l->head; */
/* 			l->head = l->head->next; */
/* 			free(tmp->line); */
/* 			free(tmp); */
/* 			i++; */
/* 		} */
/* 	} */
/* } */
