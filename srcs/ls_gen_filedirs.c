/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_gen_filedirs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 12:22:52 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	ls_gen_filedirs_sort(char *options, t_arraylist *filedirs)
{
	if (!filedirs)
		return ;
	if (ft_strchr(options, 't'))
		filedirs->sort(filedirs, ls_filedir_t_cmp);
	else
		filedirs->sort(filedirs, ls_filedir_cmp);
}

t_arraylist	*ls_gen_filedirs(char *options, t_filedir *temp_filedir)
{
	t_arraylist		*filedirs;
	DIR				*curr_dir;
	t_dirent		*dir_entry;
	char			*root;
	char			*full_path;

	if (!(curr_dir = opendir(temp_filedir->path)))
		return (ls_perror(temp_filedir->name));
	root = ft_strjoin(temp_filedir->path, "/");
	filedirs = NULL;
	while ((dir_entry = readdir(curr_dir)) != NULL)
	{
		full_path = ft_strjoin(root, dir_entry->d_name);
		if (!(temp_filedir = filedir(full_path)))
			continue;
		if (!filedirs)
			filedirs = check_malloc(arraylist(temp_filedir, DIR_BUF));
		else
			filedirs->push(filedirs, temp_filedir);
		free(full_path);
	}
	closedir(curr_dir);
	ls_gen_filedirs_sort(options, filedirs);
	free(root);
	return (filedirs);
}
