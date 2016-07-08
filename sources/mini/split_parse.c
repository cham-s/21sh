/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:33:18 by cattouma          #+#    #+#             */
/*   Updated: 2016/03/16 08:56:34 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	to_allocate(const char *s)
{
	size_t	size;

	size = 0;
	while (ft_isspace(*s) && *s)
		s++;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if ((*s && (!ft_isspace(*s))) && ((ft_isspace(*(s + 1)))
					|| *(s + 1) == '\0'))
			size++;
		if (*s)
			s++;
	}
	return (size);
}

static size_t	ft_strlenchar(const char *s)
{
	size_t i;

	i = 0;
	while (ft_isspace(*s) && *s)
		s++;
	while (!ft_isspace(*s) && *s)
	{
		i++;
		s++;
	}
	return (i);
}

/*
 * check if the splitted string is a token then replace it
 * with its corresponding value
 */

static char			*replace_symbol(char *s, t_dict **dicts)
{
	char	*key;
	int		slash_pos;

	slash_pos = ft_strchr(s, '/') - s;
	if ((key = is_tokenstr(s)))
	{
		if (slash_pos == 2 || slash_pos == 1)
		{
			if (replace_s(&s, dicts, &key, slash_pos) == -1)
				return (s);
		}
		else
		{
			if (replace_all(&s, dicts, &key) == -1)
				return (s);
		}
	}
	return (s);
}

/*
 * split the line then parse it to check for shell token
 */

char			**split_parse(char const *s, t_dict **dicts)
{
	char	**new;
	size_t	len;
	size_t	i;
	size_t	strlen;

	if (s == NULL)
		return (NULL);
	i = 0;
	strlen = 0;
	len = to_allocate(s);
	new = (char **)ft_memalloc(len + 1);
	if (!new)
		return (NULL);
	while (len--)
	{
		while (ft_isspace(*s))
			s++;
		strlen = ft_strlenchar(s);
		new[i] = ft_strndup(s, strlen);
		new[i] = replace_symbol(new[i], dicts);
		s += strlen;
		i++;
	}
	new[i] = NULL;
	return (new);
}
