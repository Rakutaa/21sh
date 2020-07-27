/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:28:53 by vkuokka           #+#    #+#             */
/*   Updated: 2020/05/17 12:03:11 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctypes.h"

int	ft_isalnum(int c)
{
	if (ft_islower(c) || ft_isupper(c) || ft_isdigit(c))
		return (1);
	return (0);
}
