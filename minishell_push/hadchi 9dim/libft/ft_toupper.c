/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:56:33 by skasmi            #+#    #+#             */
/*   Updated: 2021/11/27 23:16:06 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int nb)
{
	if (nb >= 97 && nb <= 122)
	{
		nb -= 32;
	}
	return (nb);
}