/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_l_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:51:57 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/29 10:06:36 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_l_info	*get_set_l_info(t_l_info *new_info)
{
	static t_l_info	*info;

	if (!new_info)
		return (info);
	info = new_info;
	return (NULL);
}
