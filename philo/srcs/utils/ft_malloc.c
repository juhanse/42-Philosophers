/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:28:23 by juhanse           #+#    #+#             */
/*   Updated: 2025/05/07 15:36:07 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	*ft_malloc(t_data *data, size_t size)
{
	void	*buffer;

	buffer = malloc(size);
	if (!buffer)
	{
		ft_free(data);
		printf(ERR_MALLOC);
		exit(EXIT_FAILURE);
	}
	return (buffer);
}
