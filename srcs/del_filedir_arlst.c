/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_filedir_arlst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 11:48:38 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		del_filedir_arlst(t_arraylist *filedirs)
{
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	iter = arlst_iter(filedirs);
	iter_ret = 1;
	while (iter_ret > 0)
	{
		temp_filedir = iter->pop(iter, &iter_ret);
		if (temp_filedir != NULL)
		{
			del_filedir(temp_filedir);
		}
	}
	free(iter);
	filedirs->del(filedirs);
}
