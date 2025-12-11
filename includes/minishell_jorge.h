
#include "libft.h"

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

typedef struct s_command
{
	char		*command;
	char		**args;
	int			argc;
	t_variable	*env;
}	t_command;

// Main command runner entrypoint.
int		run_command(t_command *com);

char	*expand_vars(const char *s, t_variable *env);
// String manipulation
char	**find_vars_in_string(char *str);

// Env management
t_variable	*set_env_value(t_variable *env, char *name, char *value);
t_variable	*del_env_value(t_variable *env, char *value);
char		*get_env_value(t_variable *env, char *name);
void		free_env(t_variable *env);
t_variable	*load_env_values(char **env);
