#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <time.h>

int chek_net(unsigned int src, unsigned int dst, unsigned int mask) { // функция, возвращающая 0, если адреса в одной подсети
    int Net_Src = src & mask;
    int Net_Dst = dst & mask;
    return Net_Src ^ Net_Dst;
}

int main(int argc, char* argv[]) { 
    if (argc != 4) { // проверка количества аргументов
        printf("Usage: % s <gateway IP> <subnet mask> <number of packets>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[3]); // Кол-во пакетов
    char ip_src[16], net_mask[16]; // Строки для заполнения из входящих аргументов
    unsigned int int_ip_src = 0, int_net_mask = 0; // Числа, которые будут содержать биты, обозначающие 'IPV4'

    // Копируем входные данные в строки
    strncpy_s(ip_src, 16, argv[1], 15);
    ip_src[15] = '\0';
    strncpy_s(net_mask, 16, argv[2], 15);
    net_mask[15] = '\0';

    printf("Gateway IP: %s\nSubnet mask: %s\nNumber of packets: %d\n", ip_src, net_mask, N);
    // Осторожно дальше примеры очень плохого кода!!!
    // Не работает по какой-то причине библиотека для перевода строк в IPV4, поэтому перевёл строки в необходимые числа
    for (int i = 0, temp_num = 0, move = 0, mult = 0; i < 15; i++) { // переводим строку net_mask в число с необходимыми битами
        if (47 < (int)(net_mask[14 - i])) { // Считываем только числа
            temp_num += (int)(((int)net_mask[14 - i] - 48) * pow(10, mult));
            mult++;
        }
        if ((net_mask[14 - i] == '.') || (i == 14)) { // Записываем байт со сдвигом в net_mask при помощи логического или

            temp_num <<= 8 * move;
            move++;
            int_net_mask |= temp_num;
            temp_num = 0;
            mult = 0;
        }
    }

    for (int i = 0, temp_num = 0, move = 0, mult = 0; i < 15; i++) { // переводим строку ip в число с необходимыми битами
        if (47 < (int)(ip_src[14 - i])) {
            temp_num += (int)(((int)ip_src[14 - i] - 48) * pow(10, mult));
            mult++;
        }
        if ((ip_src[14 - i] == '.') || (i == 14)) { // Записываем байт со сдивгом в ip_src при помощщи логического или
            temp_num <<= 8 * move;
            move++;
            int_ip_src |= temp_num;
            temp_num = 0;
            mult = 0;
        }
    }
    
    unsigned int for_interval = int_ip_src & int_net_mask; // подсеть
    // дальше можно выбрать разброс
    //int MIN = for_interval, MAX = for_interval + 255; // все адреса в той же подсети
    int MIN = for_interval - N/2, MAX = for_interval + N/2; // средний разброс
    //int MIN = for_interval - N, MAX = for_interval + N; // большой разброс
    //int MIN = 1, MAX = 0xFFFFFFFF; // максимальный разброс

    unsigned int n;
    srand(time(NULL));
    int same_net = 0;
    for (int i = 0; i < N; i++) { // рандомизируются назначения пакетов
        n = MIN + rand() % (MAX - MIN);
        if (chek_net(int_ip_src, n, int_net_mask) == 0) // совпадение подсетей
            same_net++;
    }
    
    printf("Same net packages: %d %lf\nAnother net packages: %d %lf\n", same_net, (double)same_net/(double)N, N - same_net, 1 - (double)same_net / (double)N);
    return 0;
}
