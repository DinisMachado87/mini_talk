/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:29:44 by dimachad          #+#    #+#             */
/*   Updated: 2025/06/09 20:54:09 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	digit(char c, int *err)
{
	if (c < '0' || c > '9')
	{
		*err = 1;
		return (0);
	}
	*err = 0;
	return (1);
}

static int	overflow(long result, int minus)
{
	if ((minus == 1 && result > 2147483647)
		|| (minus == -1 && result > 2147483648))
		return (1);
	return (0);
}

static int	handle_error(int *err)
{
	*err = 1;
	return (0);
}

int	ft_atoi(char *nptr, int *err)
{
	int		minus;
	long	result;

	minus = 1;
	result = 0;
	while (space(*nptr))
		nptr++;
	if (*nptr == '-')
		minus = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	if (!digit(*nptr, err))
		return (handle_error(err));
	while (*nptr == '0')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		if (overflow(result, minus) || !digit(*nptr, err))
			return (handle_error(err));
		nptr++;
	}
	if (*nptr)
		return (handle_error(err));
	return (minus * (int)result);
}
