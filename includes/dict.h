/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:35:08 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/16 09:41:32 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H
# include "libft.h"
# define INIT_SIZE			30
# define MULTIPLAYER		97
# define GROWTH_FACTOR		2
# define MAX_LOAD_FACTOR	1

typedef struct		s_elt
{
	char			*key;
	char			*value;
	struct s_elt	*next;
}					t_elt;

typedef struct		s_dict
{
	int				size;
	int				n;
	t_elt			**table;
}					t_dict;

unsigned long		hash_function(const char *s);
void				grow(t_dict *d);
t_dict				*dict_create(void);
void				dict_destroy(t_dict *dict);
void				dict_insert(t_dict *d, const char *key, const char *value);
char				*dict_search(t_dict *d, const char *key);
void				dict_delete(t_dict *d, const char *key);

#endif
