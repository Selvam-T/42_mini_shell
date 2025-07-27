/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsung <emsung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 01:38:33 by emma              #+#    #+#             */
/*   Updated: 2024/04/19 14:05:38 by emsung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell2.h"
# include "minishell_utils.h"
# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

//(1) MAIN
int		init(t_minishell **shell, char **env, int ac, char **av);
void	run_shell(t_minishell *shell);
int		run_input(char **args, t_minishell *shell);

//(2) READ INPUT
int		read_input(t_minishell *shell, char ***ptr);
int		readline_with_signals(t_minishell *shell, char **input);
char	**format_input(t_minishell *shell, char **input);

//SIGNAL
void	sighandler_sigint_rl(int sig);
void	sighandler_eof_heredoc(int sig);
void	sighandler_sigint_processes(int sig);

//EXIT STATUS
void	update_exitstatus(int num);
int		*storage_exitstatus(void);

/* LEXER -----------------------------------------------------------------------
	|
   	-->	TOKENIZER
   	|		TRAVERSES CHAR **ARGS AND INITIALIZES TOKENIZED STRING OF T_INPUT *
   	|			NODE SETUP
	|				2 TYPES OF T_INPUT:
	| 					1. OPERATOR NODE
	|  					2. COMMAND NODE (T_INPUT->CONTENT CONTAINS T_CMD)
	|			
	|
	|	TOKENIZED STRING EG: ( ECHO HELLO && ECHO BYE)
	|		ID:			 1      2     3     4    5
	|		TOKEN:	OPEN_BRAC  CMD  OP_AND  CMD  CLOSE_BRAC
	|		CONTENT: 
	|			|
	|			v
	|		(A) OPERATOR NODE CONTENT EG: &&
	|			CONTENT (CHAR *): "&&"
	|
	|		B)	COMMAND NODE CONTENT (T_CMD *) EG: CAT INFILE > OUTFILE
	|			ARGS: "CAT" "INFILE"
	|			REDIRS: ">" "OUTFILE"
   	|
   	-->	SYNTAX ANALYSIS
   	|		CHECK UNCLOSED BRACKETS
   	|		CHECK OPERATORS ARE LINKED TO COMMANDS
----------------------------------------------------------------------------*/

//LEXER -- MAIN
int		lexer(char **args, t_minishell *shell);

//LEXER -- SYNTAX ANALYSIS -- MAIN
int		syntax_check_command(t_input *string);
int		syntax_analyzer(t_input *head);

//LEXER -- SYNTAX ANALYSIS -- CHECKS
int		syntax_check_brac_set(t_input **open, t_input **close, int *c, int *s);
int		syntax_check_brackets(t_input *string);
int		syntax_check_oper_left(t_input *head);
int		syntax_check_oper_right(t_input *head);
int		syntax_check_operators(t_input *string);

//LEXER -- TOKENIZER
void	tok_add_operator_node(char **args, t_input **head, int *id);
int		tok_add_command_node(char ***args, t_input **head, int *id);
int		tokenizer(char **args, t_minishell *shell);

//LEXER -- TOKENIZER -- NODE SETUP
int		countnum_args_redirs(char **args, int *count_args, int *count_redirs);
t_cmd	*init_cmd(char **args);
t_cmd	*set_cmd_node(char ***args);
t_input	*init_input_node(int token, void *content, int id);

//LEXER -- TOKENIZER -- UTILS
void	add_new_node(t_input **head, t_input *new);
int		is_operator(char *s, int len, int count_redir);
int		tok_operator(char *s);
char	*token_str(int id);
t_input	*find_lastnode(t_input *head);

/* PARSER ----------------------------------------------------------------------
	|
	(RECURSION)
	|
   	-->	WHILE SEARCHING PRIORITY NODE
   	|		1. SEARCH AND OR
   	|		2. SEARCH PIPE
   	|		IF NO MORE BRACKETS TO ENTER
   	|			3. SEARCH COMMAND
   	|
   	--> ONCE FOUND NODE
   	|		DUP NODE ADDED TO TREE
   	|
   	--> REPEAT FOR TREE->LEFT AND TREE->RIGHT
   	|
   (TREE BRANCH ENDS WHEN NODE IS COMMAND)
----------------------------------------------------------------------------*/

//PARSER -- MAIN
int		recursive_parse_tree(t_input *start, t_input *end, t_input **t, int i);
int		parser(t_minishell *shell);

//PARSER -- SEARCH PRIORITY NODE
int		search_op_and_or(t_input *start, t_input *end, t_input **find);
int		search_op_pipe(t_input *start, t_input *end, t_input **find);
int		search_command(t_input *start, t_input *end, t_input **find);

//PARSER -- DUP FOUND NODE
t_cmd	*free_cmd_malloc_fail(char	***ptr1, void **ptr2);
t_cmd	*dup_cmd_content(t_cmd *node_cmd);
t_input	*dup_input_node(t_input *node);
int		dup_input_content(t_input **node, t_input **ret);
int		set_tree_node_is_command(t_input **tree, t_input *found, int c_brac);

//PARSER -- SKIP BRACKETS
void	skip_inner_brackets(t_input **input, t_input *end, int *flag_bracket);
t_input	*skip_brackets(t_input *node, t_input *end);
int		adjusted_startend(t_input *cur, t_input **startend, int *c, int tok);
int		enter_brackets(t_input **start, t_input **end);

/* REDIRS AND EXPANSIONS -------------------------------------------------------
	|
	|(DONE JUST BEFORE COMMAND IS EXECUTED)
	|
	|--> REDIRECTIONS (T_CMD->CHAR **REDIRS)
	|			ITERS THROUGH REDIRS
	|				OPENS ANY FILES AND DUPS FILE DESCRIPTOR TO STDIN/OUT
	|
	|--> EXPANSIONS (T_CMD->CHAR **ARGS AND CHAR **REDIRS)
	|			ITERS THROUGH ARGS AND REDIRS
	|				EXPANSION OF ENVIRONMENT VARIABLES
	|				EXPANSION OF WILDCARDS
----------------------------------------------------------------------------*/

//REDIRECTIONS -- MAIN
int		perror_open(t_minishell *shell, char *filename, int flag);
int		open_files(t_minishell *shell, char **redirs, int *rdin, int *rdout);
int		redirections(t_minishell *shell, t_cmd *cmd, int *pipes);

//REDIRECTIONS -- HEREDOC
void	write_buffstr_to_fd(t_minishell *shell, char **buff_str, int *fds);
char	*read_until_limiter(char *limiter);
int		redir_heredoc(t_minishell *shell, char *limiter, int *pipes);

//EXPANDER -- MAIN
char	**expanded_args(t_minishell *shell, char **args);
void	expansions(t_minishell *shell, t_cmd *cmd);

/* EXECUTOR --------------------------------------------------------------------
	|
	(RECURSIVELY TRAVERSES PARSE TREE)
----------------------------------------------------------------------------*/
//EXECUTOR -- MAIN
void	recursive_env_update(t_minishell *shell, t_input *tree, int pipe_check);
int		recursive_executor(t_minishell *shell, t_input *tree, int *pipes);
void	executor(t_minishell *shell);

//EXECUTOR -- ANDOR
void	exec_prev_builtin(t_minishell *shell, t_input *tree);
int		exec_andor_fail(t_input *tree, int status);
int		execute_handle_andor(t_minishell *shell, t_input *tree, int *pipes);

//EXECUTOR -- PIPE
int		recursive_check_heredoc(t_input *tree);
int		close_wait_pipe(int *fds, int *pids, int flag, int status2);
int		exec_pipe_left(t_minishell *shell, t_input *node, int *fd, int *pipes);
int		exec_pipe_right(t_minishell *shell, t_input *node, int *fd, int *pipes);
int		execute_handle_pipe(t_minishell *shell, t_input *node, int *pipes);

//EXECUTOR -- COMMAND
int		check_emptystr(char *str);
int		handle_empty_args(t_minishell *shell, t_cmd *cmd, int flag, int *i);
int		ft_execute(t_minishell *shell, t_cmd *cmd, int i);
int		execute_handle_cmd(t_minishell *shell, t_cmd *cmd, int *pipes);

//EXECUTOR -- EXECVE UTILS
void	perror_eacces(t_minishell *shell, t_cmd *cmd, int i, char **pathname);
void	perror_execve(t_minishell *shell, t_cmd *cmd, int i, char **pathname);
void	perror_shellscript(char *cmd, char **pathname);
char	*find_pathname(char *cmd, char **env);
char	*ft_getenv(char **env, char *var_name);
void	ft_execve(t_minishell *shell, t_cmd *cmd, int i);

//UTILS
void	error_exit(char *s);
char	*print_ret_null(char *str);
int		count_doubleptr_len(char **ptr);
void	ft_argscat(char ***dst, char **src);
char	**ft_argsjoin(char **args1, char **args2);

//FREE -- GENERAL
t_cmd	*free_cmd_malloc_fail(char	***ptr1, void **ptr2);
void	exit_free_all(t_minishell *shell, int exit_num, int flag);
void	free_all(t_minishell *shell, int flag);

//FREE -- STRUCTS
void	free_struct_oper(t_oper **ptr);
void	free_struct_cmd(t_cmd **ptr);
void	free_input_str(t_input *str);
void	free_input_tree(t_input **input);

//DEBUG
void	print_doubleptr(char **ptr);
void	print_string_content(t_input *head);
void	print_parse_string(t_input *head);
void	print_tree_found_hierarchy(t_input *found);
int		print_parse_tree(t_input *tree, int i);
int		print_errmsg(char *s1, char *ptr, char *s3);

#endif