/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_buckle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 14:22:56 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 14:26:13 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ls_buckle(char *options, t_arraylist *filedirs)
{
	if (!filedirs)
		return ;
	ls_print(options, filedirs);
	if (ft_strchr(options, 'R'))
		ls_loop(options, filedirs, 0);
}
