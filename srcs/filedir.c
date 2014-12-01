/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/01 18:56:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_filedir	*filedir(char *input_path)
{
	t_filedir	*neofiledir;

	neofiledir = check_malloc(malloc(sizeof(t_filedir)));
	if (ft_strncmp(input_path, "./", 2) && *input_path != '/')
		neofiledir->path = ft_strjoin("./", input_path);
	else
		neofiledir->path = ft_strdup(input_path);
	neofiledir->name = ft_strrchr(neofiledir->path, '/') + 1;
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
