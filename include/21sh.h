/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cattouma <cattouma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 21:30:06 by cattouma          #+#    #+#             */
/*   Updated: 2016/07/10 19:28:57 by cattouma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWENTYONE_H
# define TWENTYONE_H
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "dict.h"
# include "tercap.h"
# include "echo.h"

// printf
# include <stdio.h>

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

typedef struct		s_line_info
{
	char	*line;
	char	**big_line;
	char	**split_line;
}					t_line_info;

t_dict				*envcpy(char **env);
void				print_env(char **env);
char				**dict_to_tab(t_dict *env);
char				*join_with_chr(char *var, char *value, char c);
int					initcmd(t_dict **dicts, t_cmd *cmd, char **line);
void				put_error(char *path, char *cmd);
void				launch_exec(t_cmd *cmd, t_dict **dicts, char **env_tab);
char				**split_parse(char const *s, t_dict **dicts);
int					ft_setenv(const char *k, const char *v, t_dict *e, int ov);
int					ft_unsetenv(const char *key, t_dict *env);
int					is_tokenchr(char c);
char				*is_tokenstr(const char *s);
int					init_tokens(t_dict **tokens);
int					init_binaries(t_dict **binaries);
void				env_missing(char *envkey);
int					is_numeric(char *s);
int					start_env(t_dict **dicts, t_cmd *cmd, char **env);
int					start_unsetenv(t_dict *env, t_cmd *cmd);
int					start_setenv(t_dict *env, t_cmd *cmd);
int					start_exit(t_dict *env, t_cmd *cmd);
int					start_cd(t_dict *env, t_cmd *cmd);
int					start_echo(t_dict *env, t_cmd *cmd);
void				ft_delsplit(char **split);
void				cmd_free(t_cmd *cmd);
void				sig_handler(int signal);
void				interpret_command(t_dict **dicts, t_cmd *cmd);
int					replace_s(char **s, t_dict **dicts, char **key, int s_pos);
int					replace_all(char **s, t_dict **dicts, char **key);
void				clean_malloc(char *line, char **big_line, char **env);
int					is_alphanumeric(const char *s);

#endif
