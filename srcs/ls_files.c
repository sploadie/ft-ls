/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 12:06:54 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_arraylist	*ls_files(t_arraylist *fldrs)
{
	t_arraylist		*files;
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*tmp_fldr;

	iter = arlst_iter(fldrs);
	files = NULL;
	iter_ret = 1;
	while (iter_ret > 0)
	{
		tmp_fldr = iter->pip(iter, &iter_ret);
		if (!ls_isdir(tmp_fldr->path))
		{
			if (!files)
				files = check_malloc(arraylist(tmp_fldr, fldrs->size(fldrs)));
			else
				files->push(files, tmp_fldr);
		}
	}
	free(iter);
	return (files);
}
