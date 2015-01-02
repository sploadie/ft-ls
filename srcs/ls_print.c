/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:44:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 11:50:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls_print(char *options, t_arraylist *filedirs)
{
	t_arlst_iter	*iter;
	int				iter_ret;
	t_filedir		*temp_filedir;

	if (!filedirs)
		return ;
	if (ft_strchr(options, 'l') || ft_strchr(options, 'F'))
		ls_l_prepare(options, filedirs);
	iter = arlst_iter(filedirs);
	if (ft_strchr(options, 'r'))
		iter->pip = iter->pop;
	iter_ret = 1;
	while (iter_ret)
	{
		temp_filedir = iter->pip(iter, &iter_ret);
		if (show_entry(options, temp_filedir->name))
		{
			if (ft_strchr(options, 'l'))
				ls_print_l(temp_filedir);
			else
				ft_putendl(temp_filedir->name);
		}
	}
	free(iter);
}
