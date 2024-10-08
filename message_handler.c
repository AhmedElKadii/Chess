#include "message_handler.h"

void init_message_queue(message_queue* queue) {
	queue->head = 0;
	queue->tail = 0;
	queue->msg_count = 0;
}

bool enqueue(message_queue *queue, const char *text, char type) {
	if (queue->msg_count == MESSAGE_QUEUE_SIZE) {
		return false;
	}

    strcpy(queue->messages[queue->tail].text, text);
    queue->messages[queue->tail].type = type;

    queue->tail = (queue->tail + 1) % MESSAGE_QUEUE_SIZE;
    queue->msg_count++;
    return true;
}

bool dequeue(message_queue *queue, message *msg) {
    if (queue->msg_count == 0) {
        return false;
    }

    *msg = queue->messages[queue->head];

    queue->head = (queue->head + 1) % MESSAGE_QUEUE_SIZE;
    queue->msg_count--;
    return true;
}

void pim(message_queue *queue, const char *text, char type) {
	enqueue(queue, text, type);
	process_messages(queue);
}

void output_message(const message *msg) {
	if (msg->type == 'e') {
		printf("\033[0;31m");
	} else if (msg->type == 'w') {
		printf("\033[0;33m");
	} else if (msg->type == 'n') {
		printf("\033[0m");
	}
	printf("\n\n%s", msg->text);
	printf("\033[0m");
}

void process_messages(message_queue *queue) {
    message msg;
    while (dequeue(queue, &msg)) {
        output_message(&msg);
    }
}
