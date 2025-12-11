
#include "libft.h"
#include <string.h>

// TODO: replace with libft. maybe add strcpy and strcat.
// Auxiliar para añadir un componente a un array de segmentos
static void append_segment(char ***segments, int *count, const char *seg)
{
    if (ft_strcmp(seg, "") == 0 || ft_strcmp(seg, ".") == 0)
        return; // ignorar vacío y "."
    if (ft_strcmp(seg, "..") == 0)
    {
        if (*count > 0)
            (*count)--; // subir un nivel
        return;
    }
    (*segments)[(*count)++] = ft_strdup(seg);
}

// Función principal
char *join_paths(const char *base, const char *relative)
{
    if (!base || !relative)
        return NULL;

    // Si relative es absoluta, ignorar base
    if (relative[0] == '/')
        base = "";

    // Separar componentes
    char **segments = malloc(256 * sizeof(char*)); // arbitrario, puede realloc
    int seg_count = 0;

    char *tmp = ft_strdup(base);
    char *tok = strtok(tmp, "/");
    while (tok)
    {
        append_segment(&segments, &seg_count, tok);
        tok = strtok(NULL, "/");
    }
    free(tmp);

    tmp = ft_strdup(relative);
    tok = strtok(tmp, "/");
    while (tok)
    {
        append_segment(&segments, &seg_count, tok);
        tok = strtok(NULL, "/");
    }
    free(tmp);

    // Construir path final
    size_t len = 1; // "/" inicial
    for (int i = 0; i < seg_count; i++)
        len += strlen(segments[i]) + 1;

    char *result = malloc(len);
    if (!result)
    {
        for (int i = 0; i < seg_count; i++)
            free(segments[i]);
        free(segments);
        return NULL;
    }

    result[0] = '\0';
    if (seg_count == 0)
        strcpy(result, "/");

    for (int i = 0; i < seg_count; i++)
    {
        strcat(result, "/");
        strcat(result, segments[i]);
        free(segments[i]);
    }
    free(segments);

    return result;
}
