#include "21sh.h"

t_history	*new_history(char *str)
{
	t_history *new;

	new = (t_history *)ft_memalloc(sizeof(*new));
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
	c->passage = 0;
	c->max = 0;
}

void	add_history(t_hcontrol *c, t_history *new)
{
	t_history		*tmp;

	tmp = c->head;
	if (!tmp)
	{
		c->head = new;
		c->list = c->head;
	}
	else
	{
		new->next = c->head;
		c->head = new;
		new->next->prev = new;
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
