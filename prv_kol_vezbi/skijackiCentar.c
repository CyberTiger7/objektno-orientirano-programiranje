//
// Created by krstevkoki on 3/25/17.
//

#include <stdio.h>

typedef struct SkiLift {
    char name[15];
    int capacity;
    int working;
} SkiLift;


typedef struct SkiCenter {
    char name[20];
    char country[20];
    SkiLift skilift[20];
    int num_skilift;
} SkiCenter;


void najgolemKapacitet(SkiCenter *sc, int n) {
    int capacity[n];
    for (int i = 0; i < n; ++i) {
        capacity[i] = 0;
    }
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sc[i].num_skilift; ++j) {
            if (sc[i].skilift[j].working == 1)
                capacity[i] += sc[i].skilift[j].capacity;
        }
    }
    int max = capacity[0];
    for (int i = 1; i < n; ++i) {
        if (max < capacity[i]) {
            max = capacity[i];
            index = i;
        } else if (max == capacity[i]) {
            if (sc[i].num_skilift > sc[i + 1].num_skilift) {
                max = capacity[i];
                index = i;
            } else {
                max = capacity[i + 1];
                index = i + 1;
            }
        }
    }
    printf("%s\n", sc[index].name);
    printf("%s\n", sc[index].country);
    printf("%d", capacity[index]);
}

int main() {
    int i, n, j;
    scanf("%d", &n);
    SkiCenter sc[10];
    for (i = 0; i < n; i++) {
        //vnesi ime
        scanf("%s", sc[i].name);
        //vnesi drzava
        scanf("%s", sc[i].country);
        //vnesi broj na liftovi
        scanf("%d", &sc[i].num_skilift);

        //za sekoj ski lift vnesi:
        //vnesi ime
        for (j = 0; j < sc[i].num_skilift; ++j) {
            scanf("%s", sc[i].skilift[j].name);
            //vnesi maksimalen broj korisnici
            scanf("%d", &sc[i].skilift[j].capacity);
            //vnesi dali e pusten vo funkcija
            scanf("%d", &sc[i].skilift[j].working);
        }

    }

    //povik na funkcijata najgolemKapacitet
    najgolemKapacitet(sc, n);
    return 0;
}