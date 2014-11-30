/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 16:30:18 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_filedir	*filedir(char *name)
{
	t_filedir	*neofiledir;

	neofiledir = check_malloc(malloc(sizeof(t_filedir)));
	if (*name == '.' || *name == '/')
	{
		neofiledir->path = ft_strdup(name);
		neofiledir->name = neofiledir->path;
	}
	else
	{
		neofiledir->path = ft_strjoin("./", name);
		neofiledir->name = neofiledir->path + 2;
	}
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->dir = opendir(neofiledir->path);
	neofiledir->stats = check_malloc(malloc(sizeof(t_stat)));
	if (stat(neofiledir->path, neofiledir->stats) == -1)
	{
		ls_perror(neofiledir->name);
		del_filedir(neofiledir);
		return (NULL);
	}
	return (neofiledir);
}
