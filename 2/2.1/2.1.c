#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
int const LENGTH = 15; // длина строк
int const NUM_OF_ADR = 100; // кол-во адресов в книге

typedef struct phone_book { // тип данных адресов дл€ телефонной книги
	char first_name[LENGTH] = "0"; // им€
	char second_name[LENGTH]; // фамили€
	char third_name[LENGTH]; // отчество
	char job[LENGTH]; // место работы
	char post[LENGTH]; // должность
	long long  phone_number; // номер телефона
	char email[LENGTH]; // почта
	char social_network[LENGTH]; // ссылка на соц.сеть
}phone_book;

void adr_out_func(phone_book* dir) { // вывод одного адреса
	if (dir->first_name[0] == '0') { // проверка на пустоту адреса
		printf("No adress\n");
		return;
	}
	printf("|First name     |Second name    |Third name     |Job            |Post           |Phone number   |Email          |Social         |");
	printf("\n|_______________|_______________|_______________|_______________|_______________|_______________|_______________|_______________|");
	printf("\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15lld|%-15s|%-15s|\n", dir->first_name, dir->second_name, dir->third_name, dir->job, dir->post, dir->phone_number, dir->email, dir->social_network);
}

void book_out_func(phone_book *dir, int amount ) { // функци€ вывода всех заполненных адресов телефонной книги
	printf("N  |First name     |Second name    |Third name     |Job            |Post           |Phone number   |Email          |Social         |");
	for (int i = 0; i < amount; i++) {
		if ((dir+i)->first_name[0] == '0') continue; // пропускает все пустые адреса
		printf("\n___|_______________|_______________|_______________|_______________|_______________|_______________|_______________|_______________|");
		printf("\n%-3d|%-15s|%-15s|%-15s|%-15s|%-15s|%-15lld|%-15s|%-15s|", i+1 ,(dir + i)->first_name, (dir + i)->second_name, (dir + i)->third_name, (dir + i)->job, (dir + i)->post, (dir + i)->phone_number, (dir + i)->email, (dir + i)->social_network);
	}
	printf("\n");
		
}

void change_adr(phone_book* dir, int num) { // функци€ изменени€ адреса
	if (((dir + num)->first_name[0] == '0')||(num>=LENGTH)||(num<1)) { // проверка адреса на существование, нельз€ мен€ть незаполненные адреса
		printf("\nNo such adr\n");
		return;
	}
	printf("Adr under num % d: \n",num+1); 
	adr_out_func(dir+num); // вывод адреса под изменение
	int choice;
	while (true){ // меню выбора дл€ изменени€ адреса
		printf("To select what to change, enter its number and press Enter.\n0 (Close)\n1 (First Name)\n2 (Second Name)\n3 (Third Name)\n4 (Job)\n5 (Post)\n6 (Phone Number)\n7 (Email)\n8 (Social)\n Perform action number ");
		scanf_s("%d", &choice);
		switch (choice) {
			scanf_s("%d", &choice);
		case 1: // им€
			printf("\nEnter First Name: ");
			scanf_s("%15s", (dir + num)->first_name, LENGTH);
			break;
		case 2: // фамили€
			printf("\nEnter Second Name: ");
			scanf_s("%15s", (dir + num)->second_name, LENGTH);
			break;
		case 3: // отчество
			printf("\nEnter Third Name: ");
			scanf_s("%15s", (dir + num)->third_name, LENGTH);
			break;
		case 4: // работа
			printf("\nEnter  Job: ");
			scanf_s("%15s", (dir + num)->job, LENGTH);
			break;
		case 5: // должность
			printf("\nEnter Post: ");
			scanf_s("%15s", (dir + num)->post, LENGTH);
			break;
		case 6: // номер телефона
			printf("\nEnter Phone number: ");
			scanf_s("%lld", &(dir + num)->phone_number);
			break;
		case 7: // почта
			printf("\nEnter Email: ");
			scanf_s("%15s", (dir + num)->email, LENGTH);
			break;
		case 8: //соцсети
			printf("\nEnter Social: ");
			scanf_s("%15s", (dir + num)->social_network, LENGTH);
			break;
		default: // выход из функции в случае ошибки или выбора функции close
			return;
		}
	}
}

void delete_adr(phone_book* dir, int num) { // функци€ удалени€ адреса
	(dir + num)->first_name[0] = '0'; // занул€етс€ им€, чтобы отметить, что адрес пуст
}

void add_adr(phone_book* dir) { // функци€ добавлени€ адреса
	int i = 0, choice;
	for (; (dir+i)->first_name[0]!='0'; i++); // нахождение первой незан€той €чейки
	printf("\nEnter new data for adress num: %d", i+1); 
	printf("\nEnter First Name: ");
	scanf_s("%15s", (dir + i)->first_name, LENGTH); // считывание имени
	printf("\nEnter Second Name: ");
	scanf_s("%15s", (dir + i)->second_name, LENGTH); // считывание фамилии
	printf("If you want to add another data input 1, else input 0: ");
	scanf_s("%d", &choice); // считывание услови€ добавлени€ необ€зательных данных в адресс
	if (choice == 1){ // считывание оставшихс€ данных
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
	else { // заполн€ютс€ пропусками
		strncpy_s((dir + i)->third_name, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->job, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->post, LENGTH, "---", LENGTH - 1);
		(dir + i)->phone_number = 000;
		strncpy_s((dir + i)->email, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->social_network, LENGTH, "---", LENGTH - 1);
	}
}

int main() {
	phone_book book1[NUM_OF_ADR]; // создание телефонной книги
	for (int i = 0; i < NUM_OF_ADR; i++)  strncpy_s(book1[i].first_name, LENGTH, "0", LENGTH - 1); // инициализаци€ first_name в каждом адресе
	for (int i = 0; i < 10; i++) { // задание адресов классическим »ваном
		strncpy_s(book1[i].first_name, LENGTH, "Ivan", LENGTH -1);
		strncpy_s(book1[i].second_name, LENGTH, "Ivanov", LENGTH - 1);
		strncpy_s(book1[i].third_name, LENGTH, "Ivanovich", LENGTH - 1);
		strncpy_s(book1[i].job, LENGTH, "Yandex", LENGTH - 1);
		strncpy_s(book1[i].post, LENGTH, "Uborshik", LENGTH - 1);
		book1[i].phone_number = 546465;
		strncpy_s(book1[i].email, LENGTH, "III@mail.ru", LENGTH - 1);
		strncpy_s(book1[i].social_network, LENGTH, "vk/III_yandex", LENGTH - 1);
	}
	int choice = 0;
	int choice_in_choice = 0;
	while (true) {
		printf("To select an action, enter its number and press Enter.\n0 (Close)\n1 (Displaying all phone book addresses)\n2 (Displaying a specific address)\n3 (Adding adress)\n4 (Change address)\n5 (Delete adress)\n Perform action number ");
		scanf_s("%d", &choice); // считывание выбранного действи€
		switch (choice){ // выбор пункта меню при помощи switch
		case 0:
			return 0; // выход из функции == конец работы программы
		case 1:
			book_out_func(book1, NUM_OF_ADR);
			break;
		case 2: // вывод конкретного адреса, нельз€ выводить пустые адреса 
			printf("\nNumber of adr: ");
			scanf_s("%d", &choice_in_choice);
			if (0 < choice_in_choice < LENGTH)
				adr_out_func(&book1[choice_in_choice-1]);
			else
				printf("\nNo such adr\n");
			break;
		case 3: // добавление адреса
			add_adr(book1);
			break;
		case 4: // изменение адреса
			printf("\nInput number of adr to change: ");
			scanf_s("%d", &choice_in_choice);
			if (0 < choice_in_choice < LENGTH)
				change_adr(book1, choice_in_choice - 1);
			else 
				printf("\nNo such adr\n");
			break;
		case 5: // удаление адреса
			printf("\nInput number of adr to delete: ");
			scanf_s("%d", &choice_in_choice);
			delete_adr(book1, choice_in_choice-1);
			break;
		default:
			printf("\nNo such function\n"); // функци€ не найдена
			break;
		}
	}
}