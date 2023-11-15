#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int const LENGTH = 15; // длина строк

// Структуры

typedef struct phone_book { // тип данных адресов для телефонной книги
	char first_name[LENGTH] = "0"; // имя
	char second_name[LENGTH]; // фамилия
	char third_name[LENGTH]; // отчество
	char job[LENGTH]; // место работы
	char post[LENGTH]; // должность
	long long  phone_number; // номер телефона
	char email[LENGTH]; // почта
	char social_network[LENGTH]; // ссылка на соц.сеть
}phone_book;

typedef struct Node { // узел, содержащий указатель на адрес
	phone_book* value;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct DblLinkedList { // структура списка
	size_t size;
	Node* head;
	Node* tail;
} DblLinkedList;

// сигнатуры

void adr_out_func(phone_book*);

void change_adr(phone_book*);

phone_book* add_adr();

// Функции для работы со списком

DblLinkedList* createDblLinkedList() { // функция создание первого элемента
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteDblLinkedList(DblLinkedList** list) { // функция удаления всего списка
	Node* tmp = (*list)->head;
	Node* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		free(tmp->value);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

void printDblLinkedList(DblLinkedList* list) { //вывод всего списка
	Node* tmp = list->head;
	int count = 0;
	printf("N  |First name     |Second name    |Third name     |Job            |Post           |Phone number   |Email          |Social         |");
	while (tmp) {
		count++;
		printf("\n___|_______________|_______________|_______________|_______________|_______________|_______________|_______________|_______________|\n%3d",count);
		adr_out_func(tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

Node* getNth(DblLinkedList* list, size_t index) { // вывод элемента по его индексу
	Node* tmp = NULL;
	size_t i;

	if (index < list->size / 2) { // если в первой половине, то поиск начинается с головы списка
		i = 0;
		tmp = list->head;
		while (tmp && i < index) {
			tmp = tmp->next;
			i++;
		}
	}
	else { // если во второй, то  с хвоста
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index) {
			tmp = tmp->prev;
			i--;
		}
	}

	return tmp;
}

void pushBack(DblLinkedList* list, phone_book* value) { // добавление в конец
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

void* deleteNth(DblLinkedList* list, size_t index) {
	Node* elm = NULL;
	void* tmp = NULL;
	elm = getNth(list, index);
	if (elm == NULL) {
		exit(5);
	}
	if (elm->prev) {
		elm->prev->next = elm->next;
	}
	if (elm->next) {
		elm->next->prev = elm->prev;
	}
	tmp = elm->value;

	if (!elm->prev) {
		list->head = elm->next;
	}
	if (!elm->next) {
		list->tail = elm->prev;
	}

	free(elm->value);
	free(elm);

	list->size--;

	return tmp;
}

// Функции для работы с адресами

void adr_out_func(phone_book* dir) { // вывод одного адреса
	if (dir->first_name[0] == '0') { // проверка на пустоту адреса
		printf("No adress\n");
		return;
	}
	printf("|%-15s|%-15s|%-15s|%-15s|%-15s|%-15lld|%-15s|%-15s|", dir->first_name, dir->second_name, dir->third_name, dir->job, dir->post, dir->phone_number, dir->email, dir->social_network);
}

void change_adr(phone_book* dir) { // функция изменения адреса
	adr_out_func(dir); // вывод адреса под изменение
	int choice;
	while (true){ // меню выбора для изменения адреса
		printf("To select what to change, enter its number and press Enter.\n0 (Close)\n1 (First Name)\n2 (Second Name)\n3 (Third Name)\n4 (Job)\n5 (Post)\n6 (Phone Number)\n7 (Email)\n8 (Social)\n Perform action number ");
		scanf_s("%d", &choice);
		switch (choice) {
			scanf_s("%d", &choice);
		case 1: // имя
			printf("\nEnter First Name: ");
			scanf_s("%15s", dir->first_name, LENGTH);
			break;
		case 2: // фамилия
			printf("\nEnter Second Name: ");
			scanf_s("%15s", dir->second_name, LENGTH);
			break;
		case 3: // отчество
			printf("\nEnter Third Name: ");
			scanf_s("%15s", dir->third_name, LENGTH);
			break;
		case 4: // работа
			printf("\nEnter  Job: ");
			scanf_s("%15s", dir->job, LENGTH);
			break;
		case 5: // должность
			printf("\nEnter Post: ");
			scanf_s("%15s", dir->post, LENGTH);
			break;
		case 6: // номер телефона
			printf("\nEnter Phone number: ");
			scanf_s("%lld", dir->phone_number);
			break;
		case 7: // почта
			printf("\nEnter Email: ");
			scanf_s("%15s", dir->email, LENGTH);
			break;
		case 8: //соцсети
			printf("\nEnter Social: ");
			scanf_s("%15s", dir->social_network, LENGTH);
			break;
		default: // выход из функции в случае ошибки или выбора функции close
			return;
		}
	}
}

phone_book* add_adr() { // функция добавления адреса
	phone_book* dir = (phone_book*)malloc(sizeof(phone_book)); // выделение памяти под адрес
	int i = 0, choice;
	printf("\nEnter new data for adress num: %d", i+1); 
	printf("\nEnter First Name: ");
	scanf_s("%15s", (dir + i)->first_name, LENGTH); // считывание имени
	printf("\nEnter Second Name: ");
	scanf_s("%15s", (dir + i)->second_name, LENGTH); // считывание фамилии
	printf("If you want to add another data input 1, else input 0: ");
	scanf_s("%d", &choice); // считывание условия добавления необязательных данных в адресс
	if (choice == 1){ // считывание оставшихся данных
		printf("\nEnter Third Name: ");
		scanf_s("%15s", (dir + i)->third_name, LENGTH);
		printf("\nEnter  Job: ");
		scanf_s("%15s", (dir + i)->job, LENGTH);
		printf("\nEnter Post: ");
		scanf_s("%15s", (dir + i)->post, LENGTH);
		printf("\nEnter Phone number: ");
		scanf_s("%lld", &(dir+i)->phone_number);
		printf("\nEnter Email: ");
		scanf_s("%15s", (dir + i)->email, LENGTH);
		printf("\nEnter Social: ");
		scanf_s("%15s", (dir + i)->social_network, LENGTH);
	}
	else { // заполняются пропусками
		strncpy_s((dir + i)->third_name, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->job, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->post, LENGTH, "---", LENGTH - 1);
		(dir + i)->phone_number = 000;
		strncpy_s((dir + i)->email, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->social_network, LENGTH, "---", LENGTH - 1);
	}
	return(dir);
}

void input_initial_data(phone_book, char[], char[], char[], char[], char[], long long,char[], char[]); // сигнатура для функции заполнения начальными данными, не доделал её

int main() {
	DblLinkedList* list = createDblLinkedList();
	long long phone_numbers[10] = { 88129264959,89264959169,84949812499,89168122921,89019654019,
								    84994725618,89812345678,88121234567,84723456789,89651234567 }; // массив с телефонными номерами
	phone_book* adr = NULL;
	for (int i = 0; i < 10; i++) { // задание адресов классическим Иваном
		adr = (phone_book*)malloc(sizeof(phone_book));
		pushBack(list, adr);
		strncpy_s(adr->first_name, LENGTH, "Ivan", LENGTH -1);
		strncpy_s(adr->second_name, LENGTH, "Ivanov", LENGTH - 1);
		strncpy_s(adr->third_name, LENGTH, "Ivanovich", LENGTH - 1);
		strncpy_s(adr->job, LENGTH, "Yandex", LENGTH - 1);
		strncpy_s(adr->post, LENGTH, "Uborshik", LENGTH - 1);
		adr->phone_number = phone_numbers[i];
		strncpy_s(adr->email, LENGTH, "III@mail.ru", LENGTH - 1);
		strncpy_s(adr->social_network, LENGTH, "vk/III_yandex", LENGTH - 1);
	}
	int choice = 0;
	int choice_in_choice = 0;
	while (true) {
		printf("To select an action, enter its number and press Enter.\n0 (Close)\n1 (Displaying all phone book addresses)\n2 (Displaying a specific address)\n3 (Adding adress)\n4 (Change address)\n5 (Delete adress)\n Perform action number ");
		scanf_s("%d", &choice); // считывание выбранного действия
		switch (choice){ // выбор пункта меню при помощи switch
		case 0:
			return 0; // выход из функции == конец работы программы
		case 1:
			printDblLinkedList(list);
			break;
		case 2: // вывод конкретного адреса, нельзя выводить пустые адреса 
			printf("\nNumber of adr: ");
			scanf_s("%d", &choice_in_choice);
			if (((size_t)choice_in_choice <= list->size) && (choice_in_choice > 0))
				adr_out_func(getNth(list, (size_t)choice_in_choice++)->value);
			else
				printf("\nAddress out of range\n");
			break;
		case 3: // добавление адреса
			pushBack(list,add_adr());
			break;
		case 4: // изменение адреса
			printf("\nInput number of adr to change: ");
			scanf_s("%d", &choice_in_choice);
			if (((size_t)choice_in_choice <= list->size) && (choice_in_choice > 0))
				change_adr(getNth(list, (size_t)choice_in_choice++)->value);
			else
				printf("\nAddress out of range\n");
			break;
			break;
		case 5: // удаление адреса
			printf("\nInput number of adr to delete: ");
			scanf_s("%d", &choice_in_choice);
			if (((size_t)choice_in_choice <= list->size) && (choice_in_choice > 0))
				deleteNth(list, (size_t)choice_in_choice++);
			else
				printf("\nAddress out of range\n");
			break;
		default:
			printf("\nNo such function\n"); // функция не найдена
			break;
		}
	}
}