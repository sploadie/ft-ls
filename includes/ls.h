/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:12:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 16:25:10 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft.h"
# include "arraylist.h"

# define OPTIONS "Ralrt"

/*
** Permitted functions:
** write
** opendir
** readdir
** closedir
** stat
** lstat
** getpwuid
** getgrgid
** listxattr
** getxattr
** time
** ctime
** readlink
** malloc
** free
** perror
** strerror
** exit
*/

typedef struct stat	t_stat;

typedef struct		s_filedir
{
	char			*name;
	size_t			name_len;
	char			*path;
	t_stat			*stats;
	DIR				*dir;
}					t_filedir;

void				ls_perror(char *s);
void				*check_malloc(void *ret);

int					isoption(char *str);
void				check_options(char *options);

void				ft_strjoinfree(char **line, char *add);
void				ft_sort_string_array(char **string_array, int size);

t_filedir			*filedir(char *name);
void				del_filedir(t_filedir *filedir);

#endif
