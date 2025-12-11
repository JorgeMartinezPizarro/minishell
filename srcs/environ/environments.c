
#include "minishell_jorge.h"
#include "libft.h"

static void *dup_env_var(void *content)
{
    t_variable *v = (t_variable *)content;
    t_variable *copy = malloc(sizeof(t_variable));
    if (!copy)
        return NULL;

    copy->name = ft_strdup(v->name);
    copy->value = ft_strdup(v->value);
    if (!copy->name || !copy->value)
    {
        free(copy->name);
        free(copy->value);
        free(copy);
        return NULL;
    }

    return copy;
}

t_list *ft_clone_env(t_list *env)
{
    return ft_lstclone(env, dup_env_var);
}

t_list *load_env_values(char **env)
{
    t_list *vars = NULL;

    while (*env)
    {
        char **s = ft_split(*env, '=');
        if (!s || !s[0])
        {
            env++;
            continue;
        }

        t_variable *v = malloc(sizeof(t_variable));
        if (!v)
        {
            if (s)
            {
                int j = 0;
                while (s[j])
                    free(s[j++]);
                free(s);
            }
            ft_lstclear(&vars, free);
            return NULL;
        }

        v->name = ft_strdup(s[0]);
        v->value = s[1] ? ft_strdup(s[1]) : ft_strdup("");

        ft_lstadd_back(&vars, ft_lstnew(v));

        int j = 0;
        while (s[j])
            free(s[j++]);
        free(s);

        env++;
    }
    return vars;
}

/* ---------------- LONGITUD ---------------- */

size_t env_len_list(t_list *vars)
{
    return ft_lstsize(vars);
}

/* ---------------- OBTENER VALOR ---------------- */

char *get_env_value(t_list *vars, char *name)
{
    while (vars)
    {
        t_variable *v = (t_variable *)vars->content;
        if (ft_strcmp(v->name, name) == 0)
            return v->value;
        vars = vars->next;
    }
    return NULL;
}

/* ---------------- AÑADIR / ACTUALIZAR ---------------- */

void set_env_value(t_list **vars, char *name, char *value)
{
    t_list *node = *vars;

    while (node)
    {
        t_variable *v = (t_variable *)node->content;
        if (ft_strcmp(v->name, name) == 0)
        {
            free(v->value);
            v->value = ft_strdup(value);
            return;
        }
        node = node->next;
    }

    // No existe, crear nuevo
    t_variable *v_new = malloc(sizeof(t_variable));
    v_new->name = ft_strdup(name);
    v_new->value = ft_strdup(value);
    ft_lstadd_back(vars, ft_lstnew(v_new));
}

/* ---------------- ELIMINAR ---------------- */

void del_env_value(t_list **vars, char *name)
{
    t_list *prev = NULL;
    t_list *curr = *vars;

    while (curr)
    {
        t_variable *v = (t_variable *)curr->content;
        if (ft_strcmp(v->name, name) == 0)
        {
            if (prev)
                prev->next = curr->next;
            else
                *vars = curr->next;

            free(v->name);
            free(v->value);
            free(v);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

/* ---------------- LIMPIAR TODAS ---------------- */

void del_variable(void *content)
{
    t_variable *v = (t_variable *)content;
    free(v->name);
    free(v->value);
    free(v);
}

void free_env(t_list **vars)
{
    ft_lstclear(vars, del_variable);
}