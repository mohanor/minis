/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:48:25 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/18 23:02:10 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	p = (char *)malloc(size * count);
	i = count * size;
	if (!p)
		return (NULL);
	ft_bzero(p, i);
	return (p);
}
