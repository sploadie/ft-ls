/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 14:04:31 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/09 14:05:00 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

unsigned int	digitc(unsigned int n)
{
	int		count;
	long	tens;

	count = 1;
	tens = 10;
	while (n >= tens)
	{
		tens = tens * 10;
		count++;
	}
	return (count);
}
