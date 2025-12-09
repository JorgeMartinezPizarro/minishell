
#include "libft.h"

typedef struct s_command
{
	char	*command;
	char	**args;
	int		argc;
	char	**env;
} t_command;

int run_command(t_command *com);