
#include "libft.h"

typedef struct s_variable
{
	char	*name;
	char	*value;
}	t_variable;

typedef struct s_command
{
	char		*command;
	char		*cwd;
	char		**args;
	size_t		argc;
	t_list		*env;
}	t_command;

// Main command runner entrypoint.
int		run_command(t_command *com);

char	*expand_vars(char *s, t_list *env);
t_list	*extract_variables(const char *str);

char	*join_paths(const char *base, const char *relative);

size_t	strarr_len(char **strs);

// Env management
size_t	env_len_list(t_list *vars);
t_list	*ft_clone_env(t_list *env);
void	set_env_value(t_list **env, char *name, char *value);
void	del_env_value(t_list **env, char *value);
char	*get_env_value(t_list *env, char *name);
void	free_env(t_list **env);
t_list	*load_env_values(char **env);
