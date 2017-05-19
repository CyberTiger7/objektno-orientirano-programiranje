//
// Created by krstevkoki on 5/19/17.
//
#include<stdio.h>

struct Pacient {
    char ime[100];
    int zdrastveno;
    int pregledi;
};

typedef struct MaticenDoktor {
    char ime[100];
    int br_pac;
    struct Pacient niza[200];
    float cena;
} doktor;

const void najuspesen_doktor(doktor *d, const int n) {
    float zarabotka[200];
    int pregledi[200];
    for (int i = 0; i < n; ++i) {
        zarabotka[i] = 0;
        pregledi[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d[i].br_pac; ++j) {
            if (d[i].niza[j].zdrastveno == 0) {
                zarabotka[i] += d[i].niza[j].pregledi * d[i].cena;
            }
            pregledi[i] += d[i].niza[j].pregledi;
        }
    }

    float max = zarabotka[0];
    int maxIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (max < zarabotka[i]) {
            max = zarabotka[i];
            maxIndex = i;
        }
        if (max == zarabotka[i]) {
            if (pregledi[maxIndex] < pregledi[i]) {
                max = zarabotka[i];
                maxIndex = i;
            }

        }
    }
    printf("%s %.2f %d", d[maxIndex].ime, max, pregledi[maxIndex]);
}

int main() {
    int i, j, n, broj;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        //ime na doktor
        scanf("%s", md[i].ime);
        //broj na pacienti
        scanf("%d", &md[i].br_pac);
        //cena na pregled
        scanf("%f", &md[i].cena);
        for (j = 0; j < md[i].br_pac; j++) {
            scanf("%s", md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);
    return 0;
}