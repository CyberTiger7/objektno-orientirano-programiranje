//
// Created by krstevkoki on 2/26/17.
//
#include <stdio.h>

struct kosnica {
    char name[50];
    float price;
    int quantity;
}proizvodi[100];


void read(int n) {
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", proizvodi[i].name);
        scanf("%f", &proizvodi[i].price);
        scanf("%d", &proizvodi[i].quantity);
    }
}

void print(int n) {
    int i;
    float total = 0;
    for (i = 0; i < n; ++i) {
        printf("%d. %s\t", i+1, proizvodi[i].name);
        printf("%.2f x ", proizvodi[i].price);
        printf("%d = %.2f\n", proizvodi[i].quantity, (proizvodi[i].price * proizvodi[i].quantity));
        total = total + proizvodi[i].price * proizvodi[i].quantity;
    }
    printf("Total: %.2f", total);
}

int main() {
    int n;
    scanf("%d", &n);
    read(n);
    print(n);
    return 0;
}
