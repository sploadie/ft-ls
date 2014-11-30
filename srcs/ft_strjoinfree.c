/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 13:59:52 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/11/30 14:00:10 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_strjoinfree(char **line, char *add)
{
	char	*to_free;

	to_free = *line;
	*line = ft_strjoin(*line, add);
	check_malloc(*line);
	free(to_free);
}
