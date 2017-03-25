//
// Created by krstevkoki on 3/25/17.
//

#include <stdio.h>
#include <string.h>

struct Proizvod {
    char code[20];
    int price;
    int stock;
};
typedef struct Proizvod Proizvod;

struct Narachka {
    char name[15];
    Proizvod products[10];
    int orders_for_product[10];
    int n;
};

typedef struct Narachka Narachka;

void sort(Proizvod *products, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (strcmp(products[j].code, products[j + 1].code) > 0) {
                Proizvod temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }

        }
    }
}

void pecatiFaktura(Narachka narachka) {
    sort(narachka.products, narachka.n);
    printf("Faktura za %s\n", narachka.name);
    int i;
    int flag = 1;
    for (i = 0; i < narachka.n; ++i) {
        if (narachka.orders_for_product[i] < narachka.products[i].stock) {
            printf("%s %d %d %d\n", narachka.products[i].code, narachka.products[i].price,
                   narachka.orders_for_product[i],
                   narachka.products[i].price * narachka.orders_for_product[i]);
            narachka.products[i].stock -= narachka.orders_for_product[i];
        } else {
            printf("Fakturata ne moze da se izgotvi\n");
            flag = 0;
            break;
        }
    }

    if (flag) {
        int vkupno = 0;
        for (i = 0; i < narachka.n; ++i) {
            vkupno += narachka.products[i].price * narachka.orders_for_product[i];
        }
        printf("Vkupnata suma na fakturata e %d", vkupno);
    }
}

int main() {

//место за вашиот код

    Narachka narachka;

    // внеси го името лицето кое ја прави нарачката
    scanf("%s", narachka.name);
    // внеси го бројот на порачани производи во нарачката
    scanf("%d", &narachka.n);
    int i;
    //за секој од нарачаните производи се внесуваат информации
    for (i = 0; i < narachka.n; ++i) {
        // внеси код
        scanf("%s", narachka.products[i].code);
        // внеси единицчна цена
        scanf("%d", &narachka.products[i].price);
        // внеси број на производи во магацин
        scanf("%d", &narachka.products[i].stock);
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j) {
        //се внесува број на производи во нарачката
        scanf("%d", &narachka.orders_for_product[j]);
    }


    // повик на функцијата pecatiFaktura
    pecatiFaktura(narachka);

    return 0;
}