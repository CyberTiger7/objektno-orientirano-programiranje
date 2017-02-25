//
// Created by krstevkoki on 2/25/17.
//

#include <stdio.h>
#include <math.h>

typedef struct tocka2D {
    double x;
    double y;
} tocka2D;

float rastojanie(tocka2D t1, tocka2D t2) {
    return sqrt((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y));
}

typedef struct tocka3D {
    // vasiot kod ovde
    double x;
    double y;
    double z;
} tocka3D;

float rastojanie3D(tocka3D t1, tocka3D t2) {
    // vasiot kod ovde
    return sqrt((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y) + (t1.z - t2.z) * (t1.z - t2.z));
}

// if true, return 1
// if false, return 0
int ista_prava(tocka2D t1, tocka2D t2, tocka2D t3) {
    // vasiot kod ovde
    return (((t2.x - t1.x) * (t3.y - t1.y) - (t2.y - t1.y) * (t3.x - t1.x)) == 0);
}

int main() {
    float x1, y1, x2, y2;

    scanf("%f %f", &x1, &y1);
    scanf("%f %f", &x2, &y2);

    tocka2D t1 = {x1, y1};
    tocka2D t2 = {x2, y2};

    float z1, z2;
    scanf("%f %f", &z1, &z2);

    tocka3D t3 = {x1, y1, z1};
    tocka3D t4 = {x2, y2, z2};

    printf("%.2f\n", rastojanie(t1, t2));
    printf("%.2f\n", rastojanie3D(t3, t4));

    tocka2D t5 = {z1, z2};
    printf("%d\n", ista_prava(t1, t2, t5));

    return 0;
}
