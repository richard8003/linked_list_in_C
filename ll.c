#include <stdio.h>
#include <stdlib.h>

// structs
struct node_s {
	int value;
	struct node_s *next;
	struct node_s *prev;
};

struct list_s {
	struct node_s *head;
	struct node_s *tail;
};

// types
typedef struct node_s node;
typedef struct list_s list;

// functions
node *create_node(int value) {
	node *result = malloc(sizeof(node));
	result->value = value;
	result->next = NULL;
	result->prev = NULL;
	return result;
}

list *create_list(int headValue) {
	node *head = create_node(headValue);
	list *result = malloc(sizeof(list));
	result->head = head;
	result->tail = head;

	return result;
}

void printList(list *list) {
	node *temporary = list->head;

	printf("\n---------------------------\n");
	int count_nodes_in_list = 0;
	while(temporary != NULL) {
		count_nodes_in_list++;
		//printf("%p ", temporary->next);

		if(temporary->prev != NULL) {
			printf("Previous node: %d\n", temporary->prev->value);
		} else {
			printf("*head node*\n");
		}
		printf("Current node value: %d\n", temporary->value);

		if(temporary->next != NULL) {
			printf("Next node value: %d\n", temporary->next->value);
		} else {
			printf("*tail node*\n");
		}

		printf("---------------------------\n");
		temporary = temporary->next;
	}
	printf("\nNumber of items in the list: %d\n\n", count_nodes_in_list);
}

void detletNode(list *list, int node_value_to_delete) {
	node *target = list->head;

	while(target != NULL) {
		if(target->value == node_value_to_delete) {
			printf("Found the node with value %d ", target->value);

			printf("\nHead: %d\n", list->head->value);
			printf("Tail: %d\n", list->tail->value);

			// if target is the TAIL AND TAIL
			if(list->head->value == node_value_to_delete &&
			   list->tail->value == node_value_to_delete) {
				printf("HEAD AND TAIL");
				list->head = NULL;
				list->tail = NULL;

				free(list->head);
				free(list->tail);
				break;
			}

			//if target is the HEAD
			if(target->value == list->head->value) {
				printf("HEAD\n");
				list->head = target->next;
				target->next->prev = NULL;
			}

			// if the node != HEAD or TAIL
			if(target->prev && target->next) {
				target->next->prev = target->prev;
				target->prev->next = target->next;
			}

			// if target is the TAIL
			if(target->value == list->tail->value) {
				printf("TAIL");
				list->tail = target->prev;
				target->prev->next = NULL;
			}

			free(target);
			break;
		}
		target = target->next;
	}
}

void append_node(list *list, node *nde) {
	list->tail->next = nde;
	nde->prev = list->tail;
	list->tail = nde;
}

int main() {
	list fubar = *create_list(1);

	append_node(&fubar, create_node(2));
	append_node(&fubar, create_node(3));

	printList(&fubar);

	printf("==================After delete=========================\n\n");

	detletNode(&fubar, 1);
	detletNode(&fubar, 2);
	detletNode(&fubar, 3);

	printList(&fubar);

	return 0;
}
