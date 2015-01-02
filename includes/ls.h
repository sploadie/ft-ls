/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 17:12:51 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 14:30:21 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>

# include "libft.h"
# include "arraylist.h"

# define OPTIONS "1ARalrt"
# define DIR_BUF 5

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

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

typedef struct			s_filedir
{
	char				*name;
	size_t				name_len;
	char				*path;
	t_stat				*stats;
	char				*link;
}						t_filedir;

typedef struct			s_l_info
{
	unsigned int		block_mem_total;
	unsigned int		link_spacing;
	unsigned int		user_spacing;
	unsigned int		group_spacing;
	unsigned int		size_spacing;
}						t_l_info;

void					*ls_perror(char *s);
void					*check_malloc(void *ret);

int						isoption(char *str);
void					check_options(char *options);

void					ft_strjoinfree(char **line, char *add);
void					ft_sort_string_array(char **string_array, int size);

t_filedir				*filedir(char *name);
void					del_filedir(t_filedir *filedir);

int						isdots(char *name);
int						show_entry(char *options, char *name);

void					del_filedir_arlst(t_arraylist *filedirs);

int						ls_filedir_cmp(t_filedir *fd1, t_filedir *fd2);
int						ls_filedir_t_cmp(t_filedir *fd1, t_filedir *fd2);

int						ls_isdir(char *path);
t_arraylist				*ls_dirs(char *options, t_arraylist *filedirs);
t_arraylist				*ls_files(t_arraylist *filedirs);
t_arraylist				*ls_gen_filedirs(char *options, t_filedir *origin_filedir);

void					ls_loop(char *options, t_arraylist *filedirs, char dots);
void					ls_buckle(char *options, t_arraylist *filedirs);
void					ls_first(char *options, t_arraylist *filedirs);

void					ls_print(char *options, t_arraylist *filedirs);
void					ls_print_l(t_filedir *filedir);
void					ls_l_prepare(char *options, t_arraylist *filedirs);
t_l_info				*get_set_l_info(t_l_info *info);
void					ls_print_sp_left(char *str, size_t space);
void					ls_print_sp_right(char *str, size_t space);

char					*uid_to_name(uid_t uid);
char					*gid_to_name(gid_t gid);

#endif
