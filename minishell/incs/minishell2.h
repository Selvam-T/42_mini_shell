/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:18:25 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:11:54 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "minishell.h"
# include "minishell_utils.h"
# include "../libs/libft/libft.h"

typedef struct s_data
{
	t_var	*usr;
	t_var	*env;
}	t_data;

//memory mgmt
void	free_doubleptr(char **ptr);
void	free_doubleptr2(char ***ptr);
void	free_var_lst(t_var **var);
void	free_str(char **str);
void	free_with_ptr(void **ptr);

//wildcard
char	**get_wc_matches(char *wildcard);

//wildcard_utils
void	update_head_tail_stars(char *wildcard, int *head_star, int *tail_star);
char	*wildcard_match(char *name, char *wildcard);

//built_in cmds
int		exec_builtin(t_minishell *ms, char *cmd, char **args);
int		execute_pwd(void);
int		execute_env(t_minishell *ms, char **args);
int		execute_unset(t_minishell *ms, char **args);
int		execute_exit(t_minishell *shell, char **args, int print);
int		execute_echo(char **args);
int		execute_cd(t_minishell *ms, char **args, int print);
int		execute_export(t_minishell *ms, char **args, int print);
int		ret_exec_builtin(t_minishell *ms, char *cmd, char **args);
int		is_notbuiltin(char *cmd);

//builtin_cmds_utils 
int		args_count(char **args);
t_var	*matched_lst(t_var *match, char *str);
char	**matched_arr(t_var *match);
int		has_wildcard(char *str);
int		ft_last_idxofchar(char *str, char c);
char	**sortstrarr(char **arg);

//env_variable
int		init_env(t_minishell *shell, char **src);
char	*get_env_value(char **env, char *find);
char	*update_env(char **env, char *find, char *value);
int		delete_env(t_minishell *shell, char *find);
int		add_env(t_minishell *shell, char *name, char *value);
int		add_apn_env(t_minishell *shell, char *name, char *append);
int		get_env_arr_index(char **env, char *find);

//env_variable_utils
void	display_env_list(char **ptr);
char	**mem_alloc(char **mem, int resize);
int		get_env_arr_index(char **env, char *find);
char	*get_env_value(char **env, char *find);
char	**index_removed_env(t_minishell *shell, int index);

//file
int		is_regularfile(char *dir);
int		is_directory(char *dir);

//CD
int		is_directory(char *dir);
int		is_regularfile(char *dir);
char	*get_cwd(void);

//input_reformat
char	**rfmt_input(char *str);
char	*clean_up_quotes(char *input);

//input_reformat_utils
int		update_str_info(char *input, int length, int **str_info);
int		count_chars(char *str);
int		count_chars2(char *str, char c);

//validate
int		is_valid_id_chr(char c, int index);
int		validate_key_val(char *key, char *val);
int		is_valid_value(char *str);
int		is_valid_key(char *key);

//validate_utils
char	*set_nonvalue(char *s, int *i, int len);
char	*extract_id_value(t_minishell *shell, char *s, int *i, int *t);

//cleanup
char	*clean_up_quotes(char *input);

//input_parser
char	**parse_argument(t_minishell *shell, char *input);

//input_parser_utils
char	*trim_quote_adv_idx(char *s, int *i, char c);
int		check_wc(char *pstr, char c, int *i);
int		count_delim(char *str, char c);
int		next_delim(char *str);

//struct_conv_utils
char	*convert_struct_chr(t_var *lst);

#endif