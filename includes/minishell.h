#ifndef MINISHELL_H
# define MINISHELL_H

// It beaks compilation, we need the global variable for the signal management.
// Fix compilation before adding it, please.

// NOTA: En el .h puedes declarar la variable, pero no definirla, eso corresponde al .c
//int	exit_status = 0;

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

extern int exit_code;

#endif