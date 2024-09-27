/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:45:56 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/27 12:45:58 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t	lock1;
pthread_mutex_t	lock2;

void*	thread1_func(void* arg)
{

	pthread_mutex_lock(&lock1); // Always lock lock1 first
	printf("Thread 1 acquired lock 1\n");

	// Simulate some work with lock1 held
	sleep(1);

	// Try to acquired lock 2
	pthread_mutex_lock(&lock2);
	printf("Thread 1 acquired lock 2\n");

	pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);

	return (NULL);
}

void*	thread2_func(void* arg)
{
	pthread_mutex_lock(&lock1); // Thread 2 also locks lock1 first
	printf("Thread 2 acquired lock 1\n");

	// Simulate some work with lock2 held
	sleep(1);

	// Try to acquired lock 1
	pthread_mutex_lock(&lock2); // Then locks lock2
	printf("Thread 2 acquired lock2\n");

	pthread_mutex_unlock(&lock2);
	pthread_mutex_unlock(&lock1);

	return (NULL);
}

int	main()
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&lock1, NULL);
	pthread_mutex_init(&lock2, NULL);

	pthread_create(&thread1, NULL, thread1_func, NULL);
	pthread_create(&thread2, NULL, thread2_func, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);

	return (0);
}