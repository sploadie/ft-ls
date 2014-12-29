/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/29 19:10:31 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		get_file_link(t_filedir *filedir)
{
	char	str[10000];
	int		link_len;

	link_len = readlink(filedir->path, filedir->link, 9999);
	if (link_len == -1)
	{
		filedir->link = NULL;
		return ;
	}
	str[link_len] = '\0';
	filedir->link = ft_strdup(str);
}

t_filedir	*filedir(char *input_path)
{
	t_filedir	*neofiledir;

	// ft_putstr("input_path: ");//FIXME//DEBUG
	// ft_putendl(input_path);//FIXME//DEBUG
	neofiledir = check_malloc(malloc(sizeof(t_filedir)));
	//PATH MUST BE VALID UPON ENTRY
	neofiledir->path = ft_strdup(input_path);
	if (ft_strchr(neofiledir->path, '/'))
	{
		neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
	}
	else
	{
		neofiledir->name = neofiledir->path;
	}
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(t_stat)));
	if (stat(neofiledir->path, neofiledir->stats) != -1)
	{
		neofiledir->link = NULL;
	}
	else if (lstat(neofiledir->path, neofiledir->stats) != -1)
	{
		get_file_link(neofiledir);
	}
	else
	{
		ls_perror(neofiledir->name);
		neofiledir->link = NULL;
		del_filedir(neofiledir);
		ft_putendl("JUMP FUCKING SHIP");//FIXME//DEBUG
		exit(1);//FIXME//DEBUG
		return (NULL);
	}
	return (neofiledir);
}
