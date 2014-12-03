/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/03 20:30:28 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_filedir	*filedir(char *input_path)
{
	t_filedir	*neofiledir;

	// ft_putstr("input_path: ");//FIXME//DEBUG
	// ft_putendl(input_path);//FIXME//DEBUG
	neofiledir = check_malloc(malloc(sizeof(t_filedir)));
	//PATH MUST BE VALID UPON ENTRY
	neofiledir->path = ft_strdup(input_path);
	if (ft_strchr(neofiledir->path, '/'))
		neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
	else
		neofiledir->name = neofiledir->path;
	neofiledir->name_len = ft_strlen(neofiledir->name);
	neofiledir->stats = check_malloc(malloc(sizeof(t_stat)));
	if (stat(neofiledir->path, neofiledir->stats) == -1)
	{
		ls_perror(neofiledir->name);
		del_filedir(neofiledir);
		return (NULL);
	}
	return (neofiledir);
}
