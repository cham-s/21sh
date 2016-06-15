/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 08:54:45 by cattouma          #+#    #+#             */
/*   Updated: 2016/06/15 10:34:55 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		is_tokenchr(char c)
{
	if (c == '-' || c == '~')
		return (1);
	return (0);
}

int		replace_s(char **s, t_dict *env, char **key, int s_pos, t_dict *dicts[DICT_COUNT])
{
	char	*tmp;
	char	*envar;

	envar = dict_search(env, dict_search(dicts[TOKENS], *key));
	if (!envar)
	{
		env_missing(dict_search(dicts[TOKENS], *key));
		return (-1);
	}
	tmp = *s;
	*s = ft_strjoin(envar, *s + s_pos);
	free(tmp);
	free(*key);
	return (0);
}

int		replace_all(char **s, t_dict *env, char **key, t_dict *dicts[DICT_COUNT])
{
	char	*tmp;
	char	*envar;

	envar = dict_search(env, dict_search(dicts[TOKENS], *key));
	if (!envar)
	{
		env_missing(dict_search(dicts[TOKENS], *key));
		return (-1);
	}
	tmp = *s;
	*s = ft_strdup(envar);
	free(tmp);
	free(*key);
	return (0);
}

char	*is_tokenstr(char *s)
{
	if (!s[1])
	{
		if (is_tokenchr(s[0]))
		{
			return (s[0] == '-' ? ft_strdup("-") : ft_strdup("~"));
		}
	}
	else if (ft_strchr(s, '/') - s == 2)
	{
		if (!ft_strncmp(s, "~+", 2) || !ft_strncmp(s, "~-", 2))
			return (ft_strndup(s, 2));
	}
	else if (ft_strchr(s, '/') - s == 1)
	{
		if (s[0] == '-' || s[0] == '~')
			return (ft_strndup(s, 1));
	}
	else if (!ft_strcmp(s, "~+") || !ft_strcmp(s, "~-"))
		return (ft_strdup(s));
	return (NULL);
}
