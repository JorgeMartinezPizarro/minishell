#include "libft.h"

t_list *ft_lstclone(t_list *lst, void *(*dup)(void *))
{
    t_list *copy = NULL;
    t_list *node;

    while (lst)
    {
        node = ft_lstnew(dup(lst->content));
        if (!node)
        {
            ft_lstclear(&copy, free);
            return NULL;
        }
        ft_lstadd_back(&copy, node);
        lst = lst->next;
    }
    return copy;
}