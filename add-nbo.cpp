//#include <QCoreApplication>
#include <stdint.h>
#include <stdio.h>

uint32_t my_ntohl(uint32_t n){
    uint32_t n1 = (n & 0XFF000000) >> 24;
    uint32_t n2 = (n & 0X00FF0000) >> 8;
    uint32_t n3 = (n & 0X0000FF00) << 8;
    uint32_t n4 = (n & 0X000000FF) << 24;
    return n1 | n2 | n3 | n4;
}

int main(int argc, char *argv[])
{
    FILE* f1;
    FILE* f2;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    uint8_t data1[5];
    uint8_t data2[5];

    if (argc != 3){
        printf("wrong input.\n");
        return 1;
    }

    if (!f1){
        printf("This file does not exist.\n");
        return 1;
    }
    fread(data1, sizeof(data1), 1, f1);

    if (!f2){
        printf("This file does not exist.\n");
        return 1;
    }
    fread(data2, sizeof(data2), 1, f2);

    uint32_t* ud1 = reinterpret_cast<uint32_t*>(data1);
    uint32_t* ud2 = reinterpret_cast<uint32_t*>(data2);

    uint32_t d1 = my_ntohl(*ud1);
    uint32_t d2 = my_ntohl(*ud2);

    int sum = d1 + d2;
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", d1, d1, d2, d2, sum, sum);

    if(fclose(f1) && fclose(f2))
        perror("fclose error\n");
    else
        printf("File closed successfully.\n");
    return 0;
}
