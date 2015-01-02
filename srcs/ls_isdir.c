/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_isdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 11:56:55 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 12:03:24 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ls_isdir(char *path)
{
	DIR	*temp_dir;

	if (!(temp_dir = opendir(path)))
		return (0);
	closedir(temp_dir);
	return (1);
}
