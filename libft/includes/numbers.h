/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 12:02:09 by vkuokka           #+#    #+#             */
/*   Updated: 2020/06/25 00:42:25 by vkuokka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBERS_H

# define NUMBERS_H

int		ft_atoi(const char *str);
int		ft_count_digits(long long nbr);
char	*ft_ftoa(long double f, int pre);
char	*ft_itoa_base(unsigned long long value, int base);
char	*ft_itoa(long long n);

#endif
