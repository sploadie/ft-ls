/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_first.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 14:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 14:26:06 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ls_first(char *options, t_arraylist *filedirs)
{
	t_arraylist	*files;
	char		*do_l;

	files = ls_files(filedirs);
	if (files)
	{
		do_l = ft_strchr(options, 'l');
		if (do_l)
			*do_l = 'F';
		ls_print(options, files);
		if (filedirs->size(filedirs) > files->size(files))
			write(1, "\n", 1);
		files->del(files);
	}
	ft_strjoinfree(&options, "^");
	ls_loop(options, filedirs, 1);
}
