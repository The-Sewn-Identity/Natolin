#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ltraj.h"
#include "util.h"

#define STDIN_POS(_stream, pos) (fseek(_stream, pos, SEEK_CUR))
#ifdef _WIN32
    #define SEPCOUNT 2
#elif __linux__
    #define SEPCOUNT 1
#endif

TrajLayout LoadTrajFile(char * filename) {
    FILE * dottraj = fopen(filename, "rb");
    if (dottraj == NULL) { perror("FAILED TO OPEN FILE"); }
    if (strstr(filename, ".traj") == NULL) { printf("WRONG FILE EXTENSION"), dottraj = NULL; }

    TrajLayout trash = malloc(16 * sizeof(Trajectory));
    unsigned short * count = malloc(sizeof(count));
    unsigned short * venum = malloc(sizeof(venum));

    for (int l=0; l < 16; l++) {
        *venum = 0;
        *count = 0;
        fscanf(dottraj, "%hu %*c%*hu", count);
        printf("[[ %d ]]\n", *count);
        trash[l].layer = l;
        trash[l].vect = malloc(*count * sizeof(Vector2));
        while (fscanf(dottraj, "%f,%f", &trash[l].vect[*venum].x, &trash[l].vect[*venum].y) == 2 
        && !feof(dottraj) && !ferror(dottraj)
        && *venum < 16) {
            *venum += 1;
        }
    }

    fclose(dottraj);
    FREEPTR(count);
    FREEPTR(venum);
    return trash;
}