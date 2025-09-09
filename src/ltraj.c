#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ltraj.h"
#include "util.h"

TrajLayout LoadTrajFile(char * filename) {
    FILE * dottraj = fopen(filename, "rb");
    if (dottraj == NULL) { perror("FAILED TO OPEN FILE"); }
    if (strstr(filename, ".traj") == NULL) { printf("WRONG FILE EXTENSION"), dottraj = NULL; }

    TrajLayout trash = malloc(16 * sizeof(Trajectory));
    unsigned short * venum = malloc(sizeof(venum));

    for (int l=0; l < 16; l++) {
        *venum = 0;
        fscanf(dottraj, "%1hu %*1c%*hu", &trash[l].count);
        // printf("[[ Layer: %d, %d ]]\n", l, *count);
        trash[l].layer = l;
        trash[l].vect_arr = malloc(16 * sizeof(Vector2));

        while (fscanf(dottraj, "%f,%f", &trash[l].vect_arr[*venum].x, &trash[l].vect_arr[*venum].y) == 2 
        && !feof(dottraj) && !ferror(dottraj)
        && trash[l].count > 2 && *venum < trash[l].count) {
            *venum += 1;
        }

        for (int g = trash[l].count; g < 16; g++) {
            trash[l].vect_arr[g] = (Vector2){0};
        }
        for (int w=0; w < 16; w++) {
            printf("Vector: %f,%f \n", trash[l].vect_arr[w].x, trash[l].vect_arr[w].y);
        }

        fseek(dottraj, -1, SEEK_CUR);
    }

    fclose(dottraj);
    FREEPTR(venum);
    return trash;
}