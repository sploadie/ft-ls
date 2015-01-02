/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_filedir_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 11:49:36 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			ls_filedir_cmp(t_filedir *fd1, t_filedir *fd2)
{
	return (ft_strcmp(fd1->name, fd2->name));
}

int			ls_filedir_t_cmp(t_filedir *fd1, t_filedir *fd2)
{
	if (fd1->stats->st_mtime < fd2->stats->st_mtime)
		return (1);
	else if (fd1->stats->st_mtime == fd2->stats->st_mtime)
		return (ft_strcmp(fd1->name, fd2->name));
	else
		return (0);
}
