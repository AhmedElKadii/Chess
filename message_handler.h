#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#include "settings.h"

typedef struct {
	char text[100];
	bool is_error;
} message;

typedef struct {
	message messages[MESSAGE_QUEUE_SIZE];
	int head;
	int tail;
	int msg_count;
} message_queue;

void init_message_queue(message_queue *queue);
bool enqueue(message_queue *queue, const char *text, bool is_error);
bool dequeue(message_queue *queue, message *msg);
void pim(message_queue *queue, const char *text, bool is_error);
void process_messages(message_queue *queue);
