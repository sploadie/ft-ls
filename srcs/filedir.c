/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/30 15:55:31 by tgauvrit         ###   ########.fr       */
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

	// ft_putstr("input_path: ");//FIXME//DEBUG//GDB
	// ft_putendl(input_path);//FIXME//DEBUG//GDB
	neofiledir = check_malloc(malloc(sizeof(t_filedir) * 2));
	//PATH MUST BE VALID UPON ENTRY
	neofiledir->path = check_malloc(ft_strdup(input_path));
	if (ft_strchr(neofiledir->path, '/'))
	{
		neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
	}
	else
	{
		neofiledir->name = neofiledir->path;
	}
	// ft_putstr("name: ");//FIXME//DEBUG//GDB
	// ft_putendl(neofiledir->name);//FIXME//DEBUG//GDB
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(struct stat)));//INCORRECT, SHOULD NOT NEED
	if (lstat(neofiledir->path, neofiledir->stats) == -1 &&
		stat(neofiledir->path, neofiledir->stats) == -1)
	{
		// ft_putendl(neofiledir->name);//FIXME//DEBUG
		ls_perror(neofiledir->path);
		neofiledir->link = NULL;
		del_filedir(neofiledir);
		// ft_putendl("JUMP FUCKING SHIP");//FIXME//DEBUG
		// exit(1);//FIXME//DEBUG
		return (NULL);
	}
	get_file_link(neofiledir);
	return (neofiledir);
}
