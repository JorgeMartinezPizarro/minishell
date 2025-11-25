/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:13:09 by jomarti3          #+#    #+#             */
/*   Updated: 2025/11/20 22:12:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
// get_next_line.c
// 
// Description:
//
// get_next_line returns the next line of the given fd. It works only with
// a single fd. NULL is returned if an read error happen or if BUFFER_SIZE=0.
//
// Notes:
//
// UB if the fd changed or if the file is binary.
// UB if you mix different fd in each read.
//
char	*get_next_line(int fd);
////////////////////////////////////////////////////////////////////////////////
// get_next_line_utils.c
////////////////////////////////////////////////////////////////////////////////
// In case of s being NULL, it returns 0.
char	*gnl_strchr(const char *s, char c);
////////////////////////////////////////////////////////////////////////////////
// In case of s being NULL, it returns 0.
size_t	gnl_strlen(const char *s);
////////////////////////////////////////////////////////////////////////////////
// It frees s1 after returning the joined string created with malloc.
char	*gnl_strjoin(char *s1, char *s2);
////////////////////////////////////////////////////////////////////////////////
// It returns a char * allocated with malloc.
char	*gnl_substr(char const *s, unsigned int start, size_t len);
////////////////////////////////////////////////////////////////////////////////
// It returns a char * allocated with malloc.
char	*gnl_strdup(char *src);
////////////////////////////////////////////////////////////////////////////////

#endif