/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 02:08:37 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:10:06 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

# define INPUT_EXPANSION 0
# define LEXER_DEBUG 0
# define SYNTAX_DEBUG 0
# define PARSER_DEBUG  0
# define EXECUTOR_DEBUG 0
# define REDIR_DEBUG 0
# define LEAKS_DEBUG 0
# define PID_DEBUG 0

# define CLOSE_BRACKET 5
# define OPEN_BRACKET 4
# define OPERATOR_OR 3
# define OPERATOR_AND 2
# define OPERATOR_PIPE 1
# define TOK_COMMAND 0

typedef struct s_input
{
	int				id;
	int				token;
	void			*content;
	struct s_input	*right;
	struct s_input	*left;
}	t_input;

typedef struct s_cmd
{
	char			**redirs;
	char			**args;
}	t_cmd;

typedef struct s_oper
{
	char	*op_str;
	int		bracket_count;
	int		andor_state;
}	t_oper;

typedef struct s_minishell
{
	int					*exit_status;
	char				**env;
	struct s_input		*tree;
}	t_minishell;

#endif
