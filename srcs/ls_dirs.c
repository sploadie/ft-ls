/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 12:04:43 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_arraylist	*ls_dirs(char *options, t_arraylist *filedirs)
{
	t_arraylist		*dirs;
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*tmp_fldr;

	iter = arlst_iter(filedirs);
	dirs = NULL;
	iter_ret = 1;
	while (iter_ret > 0)
	{
		tmp_fldr = iter->pip(iter, &iter_ret);
		if (!S_ISDIR(tmp_fldr->stats->st_mode))
		{
			if (!ls_isdir(tmp_fldr->path))
				continue;
			if (ft_strchr(options, 'l'))
				continue;
		}
		if (!dirs)
			dirs = check_malloc(arraylist(tmp_fldr, filedirs->size(filedirs)));
		else
			dirs->push(dirs, tmp_fldr);
	}
	free(iter);
	return (dirs);
}
