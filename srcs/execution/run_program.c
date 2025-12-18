#include "minishell_jorge.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char **env_list_to_envp(t_list *env)
{
	int len = ft_lstsize(env);
	char **envp = ft_calloc(len + 1, sizeof(char *));
	t_list *node = env;
	int i = 0;

	while (node)
	{
		t_variable *var = (t_variable *)node->content;
		envp[i] = ft_strjoin(var->name, "=");
		char *tmp = ft_strjoin(envp[i], var->value);
		free(envp[i]);
		envp[i] = tmp;
		node = node->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}

char *find_executable(const char *cmd)
{
	char *path_env;
	char **dirs;
	char *full;
	int i;

	if (ft_strchr(cmd, '/')) // contiene '/' → ruta directa
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}

	path_env = getenv("PATH");
	if (!path_env)
		return NULL;

	dirs = ft_split(path_env, ':');
	if (!dirs)
		return NULL;

	i = 0;
	while (dirs[i])
	{
		full = join_paths(dirs[i], cmd);
		if (access(full, X_OK) == 0)
		{
			free_str_array(dirs); // liberar tu función de array de strings
			return full;
		}
		free(full);
		i++;
	}

	free_str_array(dirs);
	return NULL; // no se encontró
}

static char **tokens_to_argv(t_tokens *tokens)
{
	int len = 0;
	t_tokens *tmp = tokens;
	char **argv;
	int i = 0;

	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}

	argv = ft_calloc(len + 1, sizeof(char *));
	if (!argv)
		return NULL;

	tmp = tokens;
	while (tmp)
	{
		argv[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	argv[i] = NULL;
	return argv;
}

int run_program(t_cmd *com)
{
	char *exe;
	char **argv;
	pid_t pid;
	int status;

	if (!com || !com->command)
		return -1;

	exe = find_executable(com->command);
	if (!exe)
	{
		ft_printf("%s: command not found\n", com->command);
		return 127;
	}

	argv = tokens_to_argv(com->args);
	if (!argv)
	{
		free(exe);
		return -1;
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(exe);
		free_str_array(argv);
		return -1;
	}
	else if (pid == 0)
	{
		char **envp = env_list_to_envp(com->env);
		execve(exe, argv, envp);
		perror("execve"); // si llega aquí hubo error
		exit(126);
	}
	else
	{
		// padre
		waitpid(pid, &status, 0);
	}

	free(exe);
	free_str_array(argv);
	return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}