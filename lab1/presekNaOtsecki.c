//
// Created by krstevkoki on 2/25/17.
//
#include <stdio.h>
#include <math.h>

typedef struct tocka {
    // vasiot kod ovde
    int x;
    int y;
} tocka;

typedef struct otsecka {
    tocka p;
    tocka q;
} otsecka;

int onSegment(tocka p, tocka q, tocka r) {
    if (q.x <= fmax(p.x, r.x) && q.x >= fmin(p.x, r.x) && q.y <= fmax(p.y, r.y) && q.y >= fmin(p.y, r.y))
        return 1;
    return 0;
}

int orientation(tocka p, tocka q, tocka r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    else if (val > 0)
        return 1;
    else
        return 2;

}

// if true, return 1
// if false, return 0
int se_secat(otsecka o1, otsecka o2) {
    // vashiot kod ovde
    int orien1 = orientation(o1.p, o1.q, o2.p);
    int orien2 = orientation(o1.p, o1.q, o2.q);
    int orien3 = orientation(o2.p, o2.q, o1.p);
    int orien4 = orientation(o2.p, o2.q, o1.q);

    if (orien1 != orien2 && orien3 != orien4)
        return 1;

    if (orien1 == 0 && onSegment(o1.p, o2.p, o1.q))
        return 1;

    if (orien2 == 0 && onSegment(o1.p, o2.q, o1.q))
        return 1;

    if (orien3 == 0 && onSegment(o2.p, o1.p, o2.q))
        return 1;

    if (orien4 == 0 && onSegment(o2.p, o1.q, o2.q))
        return 1;

    return 0;
}

int main() {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    tocka t1 = {x1, y1};
    tocka t2 = {x2, y2};
    otsecka o1 = {t1, t2};

    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    tocka t3 = {x1, y1};
    tocka t4 = {x2, y2};
    otsecka o2 = {t3, t4};

    printf("%d\n", se_secat(o1, o2));
    return 0;
}