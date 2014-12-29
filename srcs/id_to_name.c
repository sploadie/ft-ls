/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_to_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 09:11:28 by tgauvrit          #+#    #+#             */
/*   Updated: 2014/12/29 09:13:27 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*uid_to_name(uid_t uid)
{
	struct passwd	*pw_ptr;

	if ((pw_ptr = getpwuid(uid)) == NULL)
		return (ft_itoa(uid));
	return (pw_ptr->pw_name);
}

char	*gid_to_name(gid_t gid)
{
	struct group	*grp_ptr;

	if ((grp_ptr = getgrgid(gid)) == NULL)
		return (ft_itoa(gid));
	return (grp_ptr->gr_name);
}