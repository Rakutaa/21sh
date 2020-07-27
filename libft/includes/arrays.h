/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:02:26 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:42:33 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_H

# define ARRAYS_H

void	ft_arrfree(char **arr);
void	ft_arriter(char **arr, void (*f)(const char *));

#endif
