/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:54:12 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 13:55:59 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	check_options(char *options)
{
	while (*options != '\0' && ft_strchr(OPTIONS, *options))
		options++;
	if (*options != '\0')
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(*options, 2);
		ft_putstr_fd("\nusage: ft_ls [-", 2);
		ft_putstr_fd(OPTIONS, 2);
		ft_putstr_fd("] [file ...]\n", 2);
		exit(1);
	}
}
