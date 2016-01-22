/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inc_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 16:45:10 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 16:46:59 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_inc_tab(char **tab, int size)
{
	char	**new;

	new = ft_create_tab(size);
	ft_freetab(tab);
	if (new)
		return (new);
	return (NULL);
}
