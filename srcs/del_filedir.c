/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_filedir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 14:20:11 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/03 20:30:18 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	del_filedir(t_filedir *filedir)
{
	free(filedir->path);
	if (filedir->stats)
		free(filedir->stats);
	free(filedir);
}
