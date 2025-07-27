PROG_NAME = minishell

SRCS_DIR = srcs/
OBJS_DIR = objs/

SRC = main.c read_input.c signal.c lexer.c tokenizer.c tok_setup_nodes.c tok_utils.c \
	  syntax.c parser.c parser_search_priority.c parser_dupnode.c parser_skipbrackets.c \
	  expander.c redir.c redir_heredoc.c executor_perror.c \
	  executor.c executor_pipe.c executor_andor.c executor_cmd.c executor_utils.c \
	  utils.c free.c free_struct.c debug.c builtin_cmd.c builtin_cmd_utils.c cd.c cleanup.c \
	  echo.c env.c env_variable.c exit.c env_variable_utils.c file.c wildcard_utils.c \
	  export.c memory_mgmt.c pwd.c input_parser_utils.c validate_utils.c \
	  input_parser.c struct_conv_utils.c unset.c validate.c wildcard.c input_reformat.c \
	  input_reformat_utils.c syntax_brac_oper.c \

SRCS = $(addprefix $(SRCS_DIR), $(SRC))
OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

LIBFT = ./libs/libft/libft.a
READLINE = -lreadline

CC = cc
FLAGS = -Wall -Werror -Wextra

all: $(PROG_NAME)

$(PROG_NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(READLINE) $(LIBFT) -o $(PROG_NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) -Iincs $(FLAGS) -Iincs -c $< -o $@

$(LIBFT):
	make all -C ./libs/libft

clean:
	make clean -C ./libs/libft
	rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C ./libs/libft
	rm -rf $(PROG_NAME)

re: fclean all
