
// TODO: write code

/*

t_variable *env is a list of pairs of strings, finished with 
NULL. replace char **env properly.

*/


// add value to env and return the char **
// free and malloc
char **set_env_value(char *name, char *value)
{
	char **new_env = 
}

// del a value from env and return the char **
// free and malloc
char **del_env_value(char *value)
{

}

char *get_env_value(char *name)
{

}

// cleanup all env
// free
void free_env(char **env)
{

}

// load static env array into malloc memory
// malloc
char **load_env_values(char **env)
{

}