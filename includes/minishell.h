/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:37:41 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/08 02:08:44 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "dict.h"
# define S_POSITION(s) (ft_strchr(s, '/') - s)

# define DICT_COUNT	3
# define ENV		0
# define TOKENS		1
# define BIN		2

typedef struct		s_cmd
{
	char	**av;
	int		ac;
	char	*exepath;
}					t_cmd;

extern t_dict		*g_tokens;

t_dict				*envcpy(char **env);
void				ft_putenv(t_dict *env);
char				**dict_to_tab(t_dict *env);
char				*join_with_chr(char *var, char *value, char c);
int					initcmd(t_dict *env, t_cmd *cmd, char **line);
void				put_error(char *path, char *cmd);
void				launch_exec(t_cmd *cmd, t_dict *env, char **env_tab);
char				**split_parse(char const *s, t_dict *env);
int					ft_setenv(const char *k, const char *v, t_dict *e, int ov);
int					ft_unsetenv(const char *key, t_dict *env);
int					is_tokenchr(char c);
char				*is_tokenstr(char *s);
int					init_tokens(t_dict *tokens);
void				env_missing(char *envkey);
int					is_numeric(char *s);
int					start_env(t_dict *env, t_cmd *cmd);
int					start_unsetenv(t_dict *env, t_cmd *cmd);
int					start_setenv(t_dict *env, t_cmd *cmd);
int					start_exit(t_dict *env, t_cmd *cmd);
int					start_cd(t_dict *env, t_cmd *cmd);
void				ft_delsplit(char **split);
void				cmd_free(t_cmd *cmd);
void				sig_handler(int signal);
void				interpret_command(t_dict *dictenv, t_cmd *cmd);
int					replace_s(char **s, t_dict *env, char **key, int s_pos);
int					replace_all(char **s, t_dict *env, char **key);
void				clean_malloc(char *line, char **big_line, char **env);
int					is_alphanumeric(const char *s);

#endif
