/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 14:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 14:38:53 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	ls_loop_return(char *options, char *path)
{
	char	*str;

	if (!(str = ft_strchr(options, '^')))
		write(1, "\n", 1);
	else
		*str = '\0';
	ft_putstr(path);
	write(1, ":\n", 2);
}

static void	ls_loop_content(char *options, t_filedir *tmp_fldr, char dots)
{
	if (isdots(tmp_fldr->name) && !dots)
		return ;
	if (show_entry(options, tmp_fldr->name) || isdots(tmp_fldr->name))
	{
		ls_loop_return(options, tmp_fldr->path);
		ls_buckle(options, ls_gen_filedirs(options, tmp_fldr));
	}
	else if (ft_strchr(options, 'R'))
		ls_loop(options, ls_gen_filedirs(options, tmp_fldr), 0);
}

void		ls_loop(char *options, t_arraylist *filedirs, char dots)
{
	t_arraylist		*dirs;
	t_arlst_iter	*iter;
	int				iter_ret;

	if (!filedirs)
		return ;
	dirs = ls_dirs(options, filedirs);
	if (!dirs)
		return ;
	iter = arlst_iter(dirs);
	if (ft_strchr(options, 'r'))
		iter->pip = iter->pop;
	iter_ret = 1;
	while (iter_ret)
	{
		ls_loop_content(options, iter->pip(iter, &iter_ret), dots);
	}
	free(iter);
	dirs->del(dirs);
	del_filedir_arlst(filedirs);
}
