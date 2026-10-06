/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char_nbr_digit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasanche <dasanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:04:57 by dasanche          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:54 by dasanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Function that prints a character and then returns 1 (characters printed)
int	ft_putchar_int_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

// Auxiliary function for putnumber to print one digit as character
void	ft_one_digit(int *count, int fd, int n)
{
	char	c;

	c = n + '0';
	write(fd, &c, 1);
	(*count)++;
}

// Function that prints an integer as character digits
int	ft_putnbr_int_fd(int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		count = 11;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count = 1;
	}
	if (n > 9)
	{
		count += ft_putnbr_int_fd(n / 10, fd);
		c = (n % 10) + '0';
		write(fd, &c, 1);
		count++;
	}
	if (n >= 0 && n <= 9)
		ft_one_digit(&count, fd, n);
	return (count);
}

// Auxiliary function for unsigned putnumber to print one digit as character
void	ft_one_unsigned_digit(unsigned int *count, int fd, int n)
{
	char	c;

	c = n + '0';
	write(fd, &c, 1);
	(*count)++;
}

// Function that prints an unsigned integer as character digits
unsigned int	ft_putnbr_unint_fd(unsigned int n, int fd)
{
	char			c;
	unsigned int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_putnbr_unint_fd(n / 10, fd);
		c = (n % 10) + '0';
		write(fd, &c, 1);
		count++;
	}
	if (n >= 0 && n <= 9)
		ft_one_unsigned_digit(&count, fd, n);
	return (count);
}
