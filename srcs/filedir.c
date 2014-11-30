/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:37:49 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 13:58:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_filedir	*filedir(char *name, t_stat *stats)
{
	t_filedir	*neofiledir;

	neofiledir = check_malloc(malloc(sizeof(t_filedir)));
	neofiledir->name = name;
	neofiledir->stats = stats;
	neofiledir->dir = NULL;
	return (neofiledir);
}
