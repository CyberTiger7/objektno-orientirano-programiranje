//
// Created by krstevkoki on 3/25/17.
//
#include <stdio.h>
#include <string.h>

#define NEDELI 4
#define DENOVI 5

// ovde strukturata RabotnaNedela

struct RabotnaNedela {
    int num_hours[DENOVI];
    int num_of_week;
};

typedef struct RabotnaNedela RN;

// ovde strukturata Rabotnik

struct Rabotnik {
    char name[50];
    RN weeks[NEDELI];
};

typedef struct Rabotnik R;

// ovde funkciite
void table(R *r, int n) {
    int sum[n], sum1[n], sum2[n], sum3[n], sum4[n];
    for (int i = 0; i < n; ++i) {
        sum[i] = 0;
        sum1[i] = 0;
        sum2[i] = 0;
        sum3[i] = 0;
        sum4[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < DENOVI; ++j) {
            sum1[i] += r[i].weeks[0].num_hours[j];
            sum2[i] += r[i].weeks[1].num_hours[j];
            sum3[i] += r[i].weeks[2].num_hours[j];
            sum4[i] += r[i].weeks[3].num_hours[j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < NEDELI; ++j) {
            for (int k = 0; k < DENOVI; ++k) {
                sum[i] += r[i].weeks[j].num_hours[k];
            }
        }
    }
    printf("Rab \t 1 \t 2 \t 3 \t 4 \t Vkupno\n");
    for (int i = 0; i < n; ++i) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", r[i].name, sum1[i], sum2[i], sum3[i], sum4[i], sum[i]);
    }
}

int maxWeek(R *r) {
    int sum[NEDELI];
    for (int i = 0; i < NEDELI; ++i) {
        sum[i] = 0;
    }
    for (int i = 0; i < NEDELI; ++i) {
        for (int j = 0; j < DENOVI; ++j) {
            sum[i] += r->weeks[i].num_hours[j];
        }
    }
    int max = sum[0];
    int index = 0;
    for (int i = 0; i < NEDELI; ++i) {
        if (max < sum[i]) {
            max = sum[i];
            index = i;
        }
    }
    return index + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    R employees[n];
    int i;
    for (i = 0; i < n; ++i) {
        scanf("%s", employees[i].name);
        int j;
        for (j = 0; j < NEDELI; ++j) {
            int k;
            for (k = 0; k < DENOVI; ++k) {
                scanf("%d", &employees[i].weeks[j].num_hours[k]);
            }

        }
    }
    printf("TABLE\n");
    table(employees, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", employees[n / 2].name);
    printf("%d\n", maxWeek(&employees[n / 2]));
    return 0;
}

