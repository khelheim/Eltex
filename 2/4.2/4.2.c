#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int RUNTIME = 5; // время длительности режима автоматической генерации в секундах

typedef struct Node{ // приоритетная очередь хранится в списке(дерево эффективнее, но планируется небольшая очередь)
	int prior;
	int processing_time;
	struct Node *next;
} Node;

void enqueue_head(Node** head, int prior, int proc_time) { // добавить в начало очереди
	Node* tmp = malloc(sizeof(Node));
	tmp->prior = prior;
	tmp->processing_time = proc_time;
	tmp->next = *head;
	*head = tmp;
}

void dequeue_head(Node** head) {
	if (*head == NULL) { // проверка на пустоту списка
		printf("Queue is empty");
		return;
	}
	Node* tmp = *head;
	*head = tmp->next;
	printf("Unqueue elem with prior %d and proccessing time %d\n", tmp->prior, tmp->processing_time);
	free(tmp);
}

void enqueue(Node** head, int prior, int proc_time) { // добавление в очередь
	Node* tmp; // переменная, для записи предыдущего элемента
	Node* new_elem = tmp = *head; // Переменная для записи нового элемента
	if ((prior > 255)||(prior < 1)) { // проверка приоритета
		printf("Priority out of range\n");
		return;
	}
	if (*head == NULL || tmp->prior > prior) { // если очередь пуста или приоритет больше чем у любого из очереди
		enqueue_head(head, prior, proc_time);
		return;
	} 
	else { // поиск элемента с меньшим приоритетом и вставка перед ним
		while (new_elem != NULL) {
			if (new_elem->prior > prior)
				break;
			tmp = new_elem;
			new_elem = new_elem->next;
		}
		new_elem = malloc(sizeof(Node));
		new_elem->prior = prior;
		new_elem->processing_time = proc_time;
		new_elem->next = tmp->next;
		tmp->next = new_elem;
	}
}

void dequeue(Node** head, int prior) { // вывод одного элемента из очереди
	if (*head == NULL) { // если список пуст
		printf("Queue is empty\n");
		return;
	}
	Node* tmp = *head, * elem_to_dequeue = *head;
	if (prior > 0) { // поиск элемента с заданным приоритетом
		do {
			if (elem_to_dequeue->prior == prior) {
				if (elem_to_dequeue != *head) { // вывод первого элемента с найденным приоритетом
					tmp->next = elem_to_dequeue->next;
					printf("Unqueue elem with prior %d and proccessing time %d\n", elem_to_dequeue->prior, elem_to_dequeue->processing_time);
					free(elem_to_dequeue);
					return;
				}
				else { // вывод первого элемента очереди
					dequeue_head(head);
					return;
				}
			}
			if (elem_to_dequeue != NULL) {
				tmp = elem_to_dequeue;
				elem_to_dequeue = elem_to_dequeue->next;
			}
		} while (elem_to_dequeue != NULL);
		printf("No element with priority %d\n", prior);
		return;
	}
	else if (prior < 0) { // вывод элемента с приоритетом ниже заданного
		while (elem_to_dequeue->next != NULL) {
			if ((elem_to_dequeue->next)->prior >= abs(prior)) {
				if (elem_to_dequeue != *head) { // вывод элемента с приоритетом ниже заданного
					tmp->next = elem_to_dequeue->next;
					printf("Unqueue elem with prior %d and proccessing time %d\n", elem_to_dequeue->prior, elem_to_dequeue->processing_time);
					free(elem_to_dequeue);
				}
				else { // вывод первого элемента очереди
					dequeue_head(head);
				}
				return;
			}
			tmp = elem_to_dequeue;
			elem_to_dequeue = elem_to_dequeue->next;
		}
		if (elem_to_dequeue->prior < abs(prior)) { // проверка последнего аргумента списка
			tmp->next = elem_to_dequeue->next;
			printf("Unqueue elem with prior %d and proccessing time %d\n", elem_to_dequeue->prior, elem_to_dequeue->processing_time);
			free(elem_to_dequeue);
			return;
		}
		printf("No element with priority lower than %d\n", abs(prior));
		return;
	}
	// вывод первого элемента очереди
	dequeue_head(head); 
	return;
}

void dequeue_to_clear(Node** head) { // вывод всей очереди, и очистка всей памяти (вспомогательная функция)
	if (*head != NULL) {
		Node* tmp = *head, * next;
		while (tmp != NULL) {
			next = tmp->next;
			printf("Unqueue elem with prior %d and proccessing time %d\n", tmp->prior, tmp->processing_time);
			free(tmp);
			tmp = next;
		}
	}
	*head = NULL;
	return;
}

void view_the_queue(Node** head) {
	if (*head == NULL) {
		printf("Queue is empty\n");
		return;
	}
	Node* tmp = *head;
	int count = 0;
	while (tmp != NULL) {
		count++;
		printf("pid: %2d  priority: %d time to comlete: %d sec\n", count ,tmp->prior,tmp->processing_time);
		tmp = tmp->next;
	}
}

int main() {
	int prior, proc_time;
	int choice = 0,now = 0, action = 0;
	Node* head = NULL;
	printf("Choose mode\n(0) Exit\n(1) Auto\n(2) Test functions\nEnter choice: ");
	scanf_s("%d", &choice); // выбор режима
	if (choice == 1) { // очень тяжёлая обработка очереди
		int action = 0; // для выбора действия;
		srand(time(NULL)); // для рандомного рандома
		for (int i = 0; i < 5 + rand() % 5; i++) { // создание от 5 до 9 элементов очереди
			enqueue(&head, 1 + rand() % 255, 2 + rand() % 5);
		}
		while (now < RUNTIME) {
			system("cls"); // очистка консоли
			printf("---Remaining operating time: %d years---\n", RUNTIME - now); // шапка, сколько времени осталось
			view_the_queue(&head);
			action = rand() % 4;
			printf("/logs/\n ");
			if (head != NULL) {
				if (head->processing_time == 0) // если время обработки первого в очереди элемента закончилось, то он извлекается
					dequeue(&head, 0);
				else
					head->processing_time--; // вычитание времени оставшегося времени обработки первого элемента
			}
			if (action > 2) { // добавляется элемент, если выпало действие 1
				prior = 1 + rand() % 255;
				proc_time = 2 + rand() % 5;
				printf("Enqueued new elem with prior %d and proccessing time %d sec\n", prior, proc_time);
				enqueue(&head, prior, proc_time);
			}
			if (action == 1) { // вывод элемента, если выпало 2 действие
				action = 1 + rand() % 4; 
				if (action == 1) { // вывод первого элемента
					printf("Dequeued first element\n");
					dequeue(&head,0);
				}
				else if (action == 2) { // вывод элемента с рандомным приоритетом
					prior = 1 + rand() % 255;
					printf("Dequeued element with priority %d\n", prior);
					dequeue(&head, prior);
				}
				else { // вывод элемента с приоритетам ниже рандомного
					prior = 1 + rand() % 255;
					printf("Dequeued element with priority lower than %d\n",prior);
					dequeue(&head, -prior);
				}
			}
			now++;
		}
		printf("\nEnter something to exit: ");
		scanf_s("%d",&action);
		system("cls");
	}
	if (choice == 2) {
		while (1) {
			printf("(0) Exit\n(1) Queue element\n(2) Unqueue element\n(3) View queue\n Enter choice: ");
			scanf_s("%d", &choice);
			printf("\n");
			switch (choice) {
			case 0: // выход/очистка очереди
				dequeue_to_clear(&head);
				return 0;
			case 1: // добавление элемента в очередь с заданным приоритетом
				printf("Enter priority: ");
				scanf_s("%d", &prior);
				printf("Enter processing time: ");
				scanf_s("%d", &proc_time);
				printf("\n");
				enqueue(&head, prior, proc_time);
				break;
			case 2: // вывод из очереди первого эл-та/с заданным приоритетом/ниже заданного приоритета
				printf("Enter priority: ");
				scanf_s("%d", &prior);
				dequeue(&head, prior);
				break;
			case 3: // вывод очереди
				view_the_queue(&head);
				break;
			default:
				printf("No option with number %d\n", choice);
				break;
			}
		}
	}
	system("cls");
	printf("----Logs:\n");
	dequeue_to_clear(&head); // очистка в конце работы программы
	return 0;
}