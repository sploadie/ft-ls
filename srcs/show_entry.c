/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 11:56:32 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/29 11:57:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		show_entry(char *options, char *name)
{
	if (*name != '.')
		return (1);
	if (ft_strchr(options, 'a'))
		return (1);
	if (ft_strchr(options, 'A') && !isdots(name))
		return (1);
	return (0);
}
