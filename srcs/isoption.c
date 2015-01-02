/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoption.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:54:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/02 10:51:22 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		isoption(char *str)
{
	if (ft_strcmp(str, "--") == 0)
		return (0);
	if (str[0] == '-' && str[1] != '\0')
		return (1);
	return (0);
}
