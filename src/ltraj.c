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
    unsigned int * count = malloc(sizeof(count));
    unsigned int * venum = malloc(sizeof(venum));

    for (int l=0; l < 16; l++) {
        *venum = 0;
        fscanf(dottraj, "%1u %*1c%*u", count);

        trash[l].count = *count;
        trash[l].layer = l;
        trash[l].vect_arr = malloc(16 * sizeof(Vector2));

        while (fscanf(dottraj, "%f,%f", &trash[l].vect_arr[*venum].x, &trash[l].vect_arr[*venum].y) == 2 
        && !feof(dottraj) && !ferror(dottraj)
        && *count >= 2 && *venum < *count) {
            *venum += 1;
        }

        for (int g = *count; g < 16; g++) {
            trash[l].vect_arr[g] = (Vector2){0};
        }

        fseek(dottraj, -1, SEEK_CUR);
    }

    fclose(dottraj);
    FREEPTR(count);
    FREEPTR(venum);
    return trash;
}

Fieldset LoadFieldset(char * filename) {
    FILE * dotfield = fopen(filename, "rb");
    Fieldset fldset;

    // https://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
    if (dotfield != NULL) {
        const size_t linesize = 256 * sizeof(char);
        char *line = (char*)malloc(linesize);

        char *cut = NULL;
        while (fgets(line, linesize, dotfield) != NULL) {
            line[strcspn(line, "\r\n")] = '\0';

            size_t size = (strlen(line) + 1) * sizeof(char);
            cut = nalloc(cut, size);
            memmove(cut, line, size);

            printf("line:\033[0;33m%s\033[0m%lld\n", cut, strlen(cut));

            uint8_t layer = 0;
            sscanf(cut, "%*[L]%hhu [^|]", &layer);
            printf("l%d\n", layer);

            // dodaj kolejną przyciętą by się nie zerowało
        scan_line:
            if ((cut = strpbrk(cut, "{")) != NULL) {
                cut++;
                printf("%s, len:%d\n", cut, strlen(cut));

                Vector2 vect;
                uint8_t vectcount = 0;

                while ((vectcount += sscanf(cut, "%f%*[,]%f", &vect.x, &vect.y))) {
                    printf("v:%f,%f\n", vect.x, vect.y);
                    if (vectcount % 2 == 0) {
                        cut += COUNTDIGITS(vect.x) + 1 + COUNTDIGITS(vect.y);
                        
                        if (cut[0] == ' ') {
                            cut++;
                        }
                        else {
                            goto scan_line;
                        }
                    }
                }
            }
        }
        if (feof(dotfield)) {
            printf("\nReached EOF.\n");
            FREEPTR(line);
        }
    }
    else {
        perror("FAILED TO OPEN FILE");      
    }
    fclose(dotfield);
    return fldset;
}