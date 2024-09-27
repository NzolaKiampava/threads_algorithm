/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:25:10 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/27 13:25:16 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare the semaphore
sem_t	semaphore;

// Thread function
void* thread_function(void* arg)
{
	int	thread_num = *((int*)arg);

	// Wait (decrement) the semaphore
	sem_wait(&semaphore);

	// Critical section
	printf("Thread %d is entering the critical section.\n", thread_num);
	sleep(2);	// Simulate some work in the critical section

	printf("Thread %d is leaving the critical section.\n", thread_num);

	// Post (increment) the semaphore
	sem_post(&semaphore);

	return (NULL);
}

int main()
{
	pthread_t threads[5];
	int thread_nums[5];

	// Initialize the semaphore to allow 3 threads in the critical section
	sem_init(&semaphore, 0, 3);

	// Create 5 threads
	int i = 0;
	while (i < 5)
	{
		thread_nums[i] = i + 1;
		pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
		i++;
	}

	// Wait for all threads to finish
	i = 0;
	while (i < 5)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	// Destroy the semaphore
	sem_destroy(&semaphore);

	return (0);
}