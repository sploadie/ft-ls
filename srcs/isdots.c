/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdots.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 11:56:53 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/09 16:08:27 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		isdots(char *name)
{
	if (!ft_strcmp(".", name) || !ft_strcmp("..", name))
		return (1);
	if (!ft_strcmp("./", name) || !ft_strcmp("../", name))
		return (1);
	return (0);
}
