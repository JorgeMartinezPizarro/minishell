#ifndef MINISHELL_H
# define MINISHELL_H

int	exit_code = 0;

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "structs.h"
# include "tokenizer.h"
# include "execution.h"
# include "parser.h"

void	expand_tokens(t_tokens **tokens, char *cwd);

#endif