
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
	char		**env; // Cambiarme a t_variable
}	t_command;

// Main command runner entrypoint.
int		run_command(t_command *com);

char	*expand_vars(const char *s, char **env);
// String manipulation
char	**find_vars_in_string(char *str);

// Env management
char	**set_env_value(char **env, char *name, char *value);
char	**del_env_value(char **env, char *value);
char	*get_env_value(char **env, char *name);
void	free_env(char **env);
char	**load_env_values(char **env);
