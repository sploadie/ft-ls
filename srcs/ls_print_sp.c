/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_sp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 14:28:18 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/01/09 16:15:04 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ls_print_sp_left(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
	write(1, str, space);
	write(1, " ", 1);
}

void	ls_print_sp_right(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	if (space < size)
		write(1, str, space);
	else
		write(1, str, size);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
	write(1, "  ", 2);
}

void	ls_print_left(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
	write(1, str, space);
}

void	ls_print_right(char *str, size_t space)
{
	size_t	size;

	size = ft_strlen(str);
	if (space < size)
		write(1, str, space);
	else
		write(1, str, size);
	while (space > size)
	{
		write(1, " ", 1);
		space--;
	}
}
