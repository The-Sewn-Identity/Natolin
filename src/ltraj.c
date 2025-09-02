#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ltraj.h"
#include "util.h"

TrajLayout LoadTrajFile(char * filename) {
    FILE * dottraj = fopen(filename, "rb");
    if (dottraj == NULL) { perror("FAILED TO OPEN FILE"); }
    if (strstr(filename, ".traj") == NULL) { printf("WRONG FILE EXTENSION"); }

    TrajLayout * trash = malloc(sizeof(Trajectory));
    //unsigned short int count = malloc(sizeof(count));
    //count = 0;

    // this sucks make it a for or something
    /* do { 
        while (fscanf(dottraj, "%hu L%hu %hu,%hu %hu,%hu %hu,%hu",
            trash[count]->layer,
            trash[count]->vect[0].x, trash[count]->vect[0].x,
            trash[count]->vect[1].x, trash[count]->vect[1].y,
            trash[count]->vect[2].x, trash[count]->vect[2].y
        ) == 7) 
        {
            trash = realloc(trash, (count + 1) * sizeof(Trajectory));
        }
    } while (!feof(dottraj) && !ferror(dottraj) && count < 16); */

    for (int l=0; l < 16; l++) {
        fseek();
        fscanf();
    }

    fclose(dottraj);
    return trash;
}