/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:02:48 by skasmi            #+#    #+#             */
/*   Updated: 2022/10/07 03:23:06 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_convert_to_lower(char *cmd)
{
    int i;

    i = 0;
    while (*cmd)
    {
        if (*cmd >= 'A' && *cmd <= 'Z')
            *cmd += 32;
        cmd++;
    }
}