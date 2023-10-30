#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
int const LENGTH = 15; // ����� �����
int const NUM_OF_ADR = 100; // ���-�� ������� � �����

typedef struct phone_book { // ��� ������ ������� ��� ���������� �����
	char first_name[LENGTH] = "0"; // ���
	char second_name[LENGTH]; // �������
	char third_name[LENGTH]; // ��������
	char job[LENGTH]; // ����� ������
	char post[LENGTH]; // ���������
	long long  phone_number; // ����� ��������
	char email[LENGTH]; // �����
	char social_network[LENGTH]; // ������ �� ���.����
}phone_book;

void adr_out_func(phone_book* dir) { // ����� ������ ������
	if (dir->first_name[0] == '0') { // �������� �� ������� ������
		printf("No adress\n");
		return;
	}
	printf("|First name     |Second name    |Third name     |Job            |Post           |Phone number   |Email          |Social         |");
	printf("\n|_______________|_______________|_______________|_______________|_______________|_______________|_______________|_______________|");
	printf("\n|%-15s|%-15s|%-15s|%-15s|%-15s|%-15lld|%-15s|%-15s|\n", dir->first_name, dir->second_name, dir->third_name, dir->job, dir->post, dir->phone_number, dir->email, dir->social_network);
}

void book_out_func(phone_book *dir, int amount ) { // ������� ������ ���� ����������� ������� ���������� �����
	printf("N  |First name     |Second name    |Third name     |Job            |Post           |Phone number   |Email          |Social         |");
	for (int i = 0; i < amount; i++) {
		if ((dir+i)->first_name[0] == '0') continue; // ���������� ��� ������ ������
		printf("\n___|_______________|_______________|_______________|_______________|_______________|_______________|_______________|_______________|");
		printf("\n%-3d|%-15s|%-15s|%-15s|%-15s|%-15s|%-15lld|%-15s|%-15s|", i+1 ,(dir + i)->first_name, (dir + i)->second_name, (dir + i)->third_name, (dir + i)->job, (dir + i)->post, (dir + i)->phone_number, (dir + i)->email, (dir + i)->social_network);
	}
	printf("\n");
		
}

void change_adr(phone_book* dir, int num) { // ������� ��������� ������
	if (((dir + num)->first_name[0] == '0')||(num>=LENGTH)||(num<1)) { // �������� ������ �� �������������, ������ ������ ������������� ������
		printf("\nNo such adr\n");
		return;
	}
	printf("Adr under num % d: \n",num+1); 
	adr_out_func(dir+num); // ����� ������ ��� ���������
	int choice;
	while (true){ // ���� ������ ��� ��������� ������
		printf("To select what to change, enter its number and press Enter.\n0 (Close)\n1 (First Name)\n2 (Second Name)\n3 (Third Name)\n4 (Job)\n5 (Post)\n6 (Phone Number)\n7 (Email)\n8 (Social)\n Perform action number ");
		scanf_s("%d", &choice);
		switch (choice) {
			scanf_s("%d", &choice);
		case 1: // ���
			printf("\nEnter First Name: ");
			scanf_s("%15s", (dir + num)->first_name, LENGTH);
			break;
		case 2: // �������
			printf("\nEnter Second Name: ");
			scanf_s("%15s", (dir + num)->second_name, LENGTH);
			break;
		case 3: // ��������
			printf("\nEnter Third Name: ");
			scanf_s("%15s", (dir + num)->third_name, LENGTH);
			break;
		case 4: // ������
			printf("\nEnter  Job: ");
			scanf_s("%15s", (dir + num)->job, LENGTH);
			break;
		case 5: // ���������
			printf("\nEnter Post: ");
			scanf_s("%15s", (dir + num)->post, LENGTH);
			break;
		case 6: // ����� ��������
			printf("\nEnter Phone number: ");
			scanf_s("%lld", &(dir + num)->phone_number);
			break;
		case 7: // �����
			printf("\nEnter Email: ");
			scanf_s("%15s", (dir + num)->email, LENGTH);
			break;
		case 8: //�������
			printf("\nEnter Social: ");
			scanf_s("%15s", (dir + num)->social_network, LENGTH);
			break;
		default: // ����� �� ������� � ������ ������ ��� ������ ������� close
			return;
		}
	}
}

void delete_adr(phone_book* dir, int num) { // ������� �������� ������
	(dir + num)->first_name[0] = '0'; // ���������� ���, ����� ��������, ��� ����� ����
}

void add_adr(phone_book* dir) { // ������� ���������� ������
	int i = 0, choice;
	for (; (dir+i)->first_name[0]!='0'; i++); // ���������� ������ ��������� ������
	printf("\nEnter new data for adress num: %d", i+1); 
	printf("\nEnter First Name: ");
	scanf_s("%15s", (dir + i)->first_name, LENGTH); // ���������� �����
	printf("\nEnter Second Name: ");
	scanf_s("%15s", (dir + i)->second_name, LENGTH); // ���������� �������
	printf("If you want to add another data input 1, else input 0: ");
	scanf_s("%d", &choice); // ���������� ������� ���������� �������������� ������ � ������
	if (choice == 1){ // ���������� ���������� ������
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
	else { // ����������� ����������
		strncpy_s((dir + i)->third_name, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->job, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->post, LENGTH, "---", LENGTH - 1);
		(dir + i)->phone_number = 000;
		strncpy_s((dir + i)->email, LENGTH, "---", LENGTH - 1);
		strncpy_s((dir + i)->social_network, LENGTH, "---", LENGTH - 1);
	}
}

int main() {
	phone_book book1[NUM_OF_ADR]; // �������� ���������� �����
	for (int i = 0; i < NUM_OF_ADR; i++)  strncpy_s(book1[i].first_name, LENGTH, "0", LENGTH - 1); // ������������� first_name � ������ ������
	for (int i = 0; i < 10; i++) { // ������� ������� ������������ ������
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
		scanf_s("%d", &choice); // ���������� ���������� ��������
		switch (choice){ // ����� ������ ���� ��� ������ switch
		case 0:
			return 0; // ����� �� ������� == ����� ������ ���������
		case 1:
			book_out_func(book1, NUM_OF_ADR);
			break;
		case 2: // ����� ����������� ������, ������ �������� ������ ������ 
			printf("\nNumber of adr: ");
			scanf_s("%d", &choice_in_choice);
			if (0 < choice_in_choice < LENGTH)
				adr_out_func(&book1[choice_in_choice-1]);
			else
				printf("\nNo such adr\n");
			break;
		case 3: // ���������� ������
			add_adr(book1);
			break;
		case 4: // ��������� ������
			printf("\nInput number of adr to change: ");
			scanf_s("%d", &choice_in_choice);
			if (0 < choice_in_choice < LENGTH)
				change_adr(book1, choice_in_choice - 1);
			else 
				printf("\nNo such adr\n");
			break;
		case 5: // �������� ������
			printf("\nInput number of adr to delete: ");
			scanf_s("%d", &choice_in_choice);
			delete_adr(book1, choice_in_choice-1);
			break;
		default:
			printf("\nNo such function\n"); // ������� �� �������
			break;
		}
	}
}