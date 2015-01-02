/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 10:53:17 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		get_file_link(t_filedir *filedir)
{
	char	str[10000];
	int		link_len;

	link_len = readlink(filedir->path, str, 9999);
	if (link_len == -1)
	{
		filedir->link = NULL;
		return ;
	}
	str[link_len] = '\0';
	filedir->link = check_malloc(ft_strdup(str));
}

t_filedir	*filedir(char *input_path)
{
	t_filedir	*neofiledir;

	neofiledir = check_malloc(malloc(sizeof(t_filedir) * 2));
	neofiledir->path = check_malloc(ft_strdup(input_path));
	if (ft_strchr(neofiledir->path, '/'))
	{
		neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
	}
	else
	{
		neofiledir->name = neofiledir->path;
	}
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(struct stat)));
	if (lstat(neofiledir->path, neofiledir->stats) == -1 &&
		stat(neofiledir->path, neofiledir->stats) == -1)
	{
		ls_perror(neofiledir->path);
		neofiledir->link = NULL;
		del_filedir(neofiledir);
		return (NULL);
	}
	get_file_link(neofiledir);
	return (neofiledir);
}
