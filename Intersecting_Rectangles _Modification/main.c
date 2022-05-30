#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FILEIN  "input.txt"
#define FILECOLOR  "color.txt"

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Rectangle {
    int id;
    Point p1;
    Point p2;
    char color[10];
} Rectangle;

int cal_area(Rectangle r) {
    return (abs(r.p1.x - r.p2.x)*abs(r.p1.y - r.p2.y));
}

typedef struct Intersecting
{
    bool f;
    Rectangle ir;
    char color[10];
    Rectangle *rec_list[100];
    int num_id;
} Intersecting;


bool insertion_rec(Rectangle r1, Rectangle *ir) {
    if(r1.p1.x >= ir->p2.x || ir->p1.x >= r1.p2.x)
        return false;
    if(r1.p1.y >= ir->p2.y || ir->p1.y >= r1.p2.y)
        return false;
    ir->p1.x = (r1.p1.x < ir->p1.x) ? ir->p1.x : r1.p1.x;
    ir->p1.y = (r1.p1.y < ir->p1.y) ? ir->p1.y : r1.p1.y;
    ir->p2.x = (r1.p2.x < ir->p2.x) ? r1.p2.x : ir->p2.x;
    ir->p2.y = (r1.p2.y < ir->p2.y) ? r1.p2.y : ir->p2.y;
    return true;
}

int main() {
    FILE *file_in;
    FILE *file_color;
    file_in = fopen(FILEIN, "r");
    file_color = fopen(FILECOLOR, "r");
    if(file_in == NULL || file_color == NULL) {
        printf("File Error!\n");
        fclose(file_in);
        fclose(file_color);   
        return 0;
    }
    char color[50][10];
    int num_color = 0;
    Rectangle rec[200];
    int num_rec = 0;
    while(fscanf(file_color, "%s", color[num_color]) == 1)
        num_color++;
    fclose(file_color); 
    int i, j;
    char s[15], c, c2;
    int id, x1, y1, x2, y2;
    bool flag;
    while(fscanf(file_in, "%c %d %c %d %c %d %c %c %d %c %d %c %s", 
                        &c, &id, &c, &x1, &c, &y1, &c, &c, &x2, &c, &y2, &c, s) == 13) {
        fscanf(file_in, "%c", &c); //\n
        //printf("%d %d %d %d %d %s\n", id, x1, y1, x2, y2, s);
        flag = false;
        for(i = 0; i < num_rec; i++) {
            if(rec[i].id == id) {
                flag = true;
                break;
            }
        }
        if(flag) {
            printf("Input error: Same identify number - #%d\n", id);
            fclose(file_in);
            return 0;
        }
        flag = true;
        for(i = 0; i < num_color; i++) {
            if(strcmp(s, color[i]) == 0) {
                flag = false;
                break;
            }
        }
        if(flag) {
            printf("Input error: The color is not in color list\n\t#%d %s\n", id, s);
            fclose(file_in);
            return 0;
        }
        rec[num_rec].id = id;
        rec[num_rec].p1.x = x1;
        rec[num_rec].p1.y = y1;
        rec[num_rec].p2.x = x2;
        rec[num_rec].p2.y = y2;
        strcpy(rec[num_rec].color, s);
        num_rec++;
    }
    fclose(file_in);

    Intersecting inter[100];
    int num_inter = 0;
    for(i = 0; i < num_rec; i++) {
        flag = true;
        for(j = 0; j < num_inter; j++) {
            if(strcmp(rec[i].color, inter[j].color) == 0) {
                if(inter[j].f) {
                    bool ret = insertion_rec(rec[i], &inter[j].ir);
                    if(ret == false)
                        inter[j].f = false;
                    else {
                        inter[j].rec_list[inter[j].num_id] = &rec[i];
                        inter[j].num_id++;
                    }
                }
                flag = false;
                break;
            }
        }
        if(flag) {
            inter[num_inter].f = true;
            inter[num_inter].ir = rec[i];
            inter[num_inter].rec_list[0] = &rec[i];
            inter[num_inter].num_id = 1;
            strcpy(inter[num_inter].color, rec[i].color);
            num_inter++;
        }
    }

    int max = 0;
    int i_max;
    for(i = 0; i < num_inter; i++) {
        if(inter[i].f == true && inter[i].num_id > 1) {
            if(inter[i].num_id > max) {
                max = inter[i].num_id;
                i_max = i;
            }
        }
    }

    if(max == 0) {
        printf("No intersection found\n");
        return 0;
    }

    printf("The largest group is a group of %s rectangles\n", inter[i_max].color);
    int x_min = INT_MAX, x_max = INT_MIN, y_min = INT_MAX, y_max = INT_MIN;
    for(i = 0; i < inter[i_max].num_id; i++) {
        printf("#%d ", inter[i_max].rec_list[i]->id);
        if(inter[i_max].rec_list[i]->p2.x > x_max)
            x_max = inter[i_max].rec_list[i]->p2.x;
        if(inter[i_max].rec_list[i]->p1.x < x_min)
            x_min = inter[i_max].rec_list[i]->p1.x;
        if(inter[i_max].rec_list[i]->p2.y > y_max)
            y_max = inter[i_max].rec_list[i]->p2.y;
        if(inter[i_max].rec_list[i]->p1.y < y_min)
            y_min = inter[i_max].rec_list[i]->p1.y;
    }
    printf("\nTheir total area is %d\n", cal_area(inter[i_max].ir));

    int total = 0;
    Rectangle check;
    int k;
    for(i = x_min; i<x_max; i++)
        for(j = y_min; j<y_max; j++) {
            check.p1.x = i;
            check.p2.x = i+1;
            check.p1.y = j;
            check.p2.y = j+1;
            for(k = 0; k < inter[i_max].num_id; k++) {
                if(insertion_rec(*inter[i_max].rec_list[k], &check)) {
                    total++;
                    break;
                }
            }
        }
    printf("Their total area is %d\n", total);

    return 0;
}