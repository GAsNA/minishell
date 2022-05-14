/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasli <aasli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:13:58 by aasli             #+#    #+#             */
/*   Updated: 2021/11/30 08:21:17 by aasli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int nb, int time)
{
	long	n;

	n = (long)nb;
	if (n < 0)
	{
		n *= -1;
		time++;
	}
	while (n >= 10)
	{
		time++;
		n = n / 10;
	}
	if (n >= 0 && n <= 9)
		time++;
	return (time);
}

static void	ft_putnbr_str(char *dst, int n, int index)
{
	if (n < 0)
		n *= -1;
	while (n >= 10)
	{
		dst[index] = n % 10 + 48;
		n = n / 10;
		index++;
	}
	if (n >= 0 && n <= 9)
	{
		dst[index] = n % 10 + 48;
	}
}

static void	ft_strrev(char *dst, int n)
{
	int		i;
	int		j;
	int		end;
	char	c;

	i = 0;
	end = ft_strlen(dst);
	j = end - 1;
	if (n < 0)
		i = 1;
	while (i <= (end - 1) / 2)
	{
		c = dst[i];
		dst[i] = dst[j];
		dst[j] = c;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*dst;

	i = 0;
	len = 0;
	len = ft_length(n, len);
	if (n == -2147483648)
		dst = ft_strdup("-2147483648");
	else
	{
		dst = (char *)malloc(len * sizeof(char) + 1);
		if (!dst)
			return (NULL);
		if (n < 0)
		{
			dst[i] = '-';
			i++;
		}
		ft_putnbr_str(dst, n, i);
		dst[len] = '\0';
		ft_strrev(dst, n);
	}
	return (dst);
}
