
// TODO: write code

/*

t_variable *env is a list of pairs of strings, finished with 
NULL. replace char **env properly.

*/


// add value to env and return the char **
// free and malloc
char **set_env_value(char **env, char *name, char *value)
{
	(void)name;
	(void)value;
	return env;
}

// del a value from env and return the char **
// free and malloc
char **del_env_value(char **env, char *value)
{
	(void)value;
	return env;
}

char *get_env_value(char **env, char *name)
{
	(void)name;
	(void)env;
	return "value";
}

// cleanup all env
// free
void free_env(char **env)
{
	(void)env;
	return;
}

// load static env array into malloc memory
// malloc
char **load_env_values(char **env)
{
	return env;
}	