#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ltraj.h"
#include "util.h"

#define STDIN_POS(_stream, pos) (fseek(_stream, pos, SEEK_CUR))
#define form_spec "%u,%u "

TrajLayout LoadTrajFile(char * filename) {
    FILE * dottraj = fopen(filename, "rb");
    if (dottraj == NULL) { perror("FAILED TO OPEN FILE"); }
    if (strstr(filename, ".traj") == NULL) { printf("WRONG FILE EXTENSION"); }

    TrajLayout trash = malloc(16 * sizeof(Trajectory));
    unsigned short * count = malloc(sizeof(count));
    
    char * temp_format = malloc(12 * sizeof("%u,%u "));
    
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

    va_list valis;

     /*for (int l=0; l < 16; l++) {
        /* while (fscanf(dottraj, "%hu L%*c%*hu", count) == 1) {
            printf("%d", *count);
            //if (*count >= 2 && *count <= 24) {
                trash[l].layer = l;
                trash[l].vect = malloc(*count * sizeof(Vector2));
                for (int r=0; r < *count; r++) {
                    strncpy(temp_format, "%u,%u ", *count * sizeof("%u,%u "));
                }
            //}
        }*/
    for (int l=0; l < 16; l++) {
        if (l < 10) {
            fscanf(dottraj, "%hu", count);
            trash[l].vect = malloc(*count * sizeof(Vector2));
            STDIN_POS(dottraj, ftell(dottraj) + 3);
            while (fscanf(dottraj, form_spec, trash[l].vect.x, *trash[l].vect.y) == 1) {

            }
            // STDIN_POS(dottraj, 2 + *count * sizeof(form_spec));
        } else {
            // STDIN_POS(dottraj, 3 + *count * sizeof(form_spec));
        }
    }

    for (int i=0; i < 16; i++){
        printf("%hu \n", trash[i].layer);
    }

    fclose(dottraj);
    return trash;
}