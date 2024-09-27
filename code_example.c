/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_example.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:50:23 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/27 10:55:07 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define BYELLOW "\e[1;33m"

pthread_mutex_t	lock;
int	shared_data = 0;

// Function that the thread will execute
void*	increment(void* arg)
{
	pthread_mutex_lock(&lock);
	shared_data++;
	printf("%sShared data: %d\n", BYELLOW, shared_data);
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1, thread2;
	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, increment, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock);
	return (0);
}
