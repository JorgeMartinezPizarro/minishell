
#include "libft.h"

typedef struct s_command
{
	char	*command;
	char	**args;
	int		argc;
	t_variable	*env; 
} t_command;

typedef struct s_variable
{
	char	*name;
	char	*value;
} t_variable;

int run_command(t_command *com);