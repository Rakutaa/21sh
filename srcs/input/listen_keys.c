/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 10:48:49 by vkuokka           #+#    #+#             */
/*   Updated: 2020/07/09 14:50:13 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "halfsh.h"
#include "keyboard.h"

/*
** After being called by loop_editor, This function waits input stream and sums
** up the ascii values received. The sum itself represents individual key.
** This key can be normal ascii character, special key and key combination
** defined in keyboard.h file.
*/

int	listen_keys(void)
{
	char	key[KEY_SIZE + 1];
	ssize_t	bytes;
	size_t	i;
	int		sum;

	bytes = read(1, key, KEY_SIZE);
	key[bytes] = '\0';
	i = -1;
	sum = 0;
	while (key[++i])
		sum += key[i];
	return (sum);
}
