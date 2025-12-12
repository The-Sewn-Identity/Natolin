#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "util.h"

/*TrajLayout LoadTrajFile(char * filename) {
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
}*/

Fieldset LoadFieldset(char * filename) {
    FILE * dotfield = fopen(filename, "rb");
    Fieldset fldset = { NULL, 0, 0, 0 };

    // https://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
    if (dotfield != NULL) {
        const size_t linesize = 256 * sizeof(char);
        char *line = malloc(linesize);

        char *cut = NULL;

        while (fgets(line, linesize, dotfield) != NULL) {
            line[strcspn(line, "\r\n")] = '\0';

            size_t size = (strlen(line) + 1) * sizeof(char);
            cut = nalloc(cut, size);
            memmove(cut, line, size);

            int8_t layer = -1;
            
            int result = sscanf(cut, "%*[L]%hhu [^|]", &layer);
            bool laychecked = (result == 1 && WITHIN(-1, 15, layer));

        scan_line:
            if ((cut = strpbrk(cut, "{")) != NULL && laychecked)
            {
                cut++;
                fldset.fieldcount++;
                
                uint8_t ind = fldset.fieldcount - 1;

                fldset.field_arr = nalloc(fldset.field_arr, fldset.fieldcount * sizeof(Field));
                fldset.field_arr[ind].point_arr.array = NULL;
                
                uint8_t vectcount = 0;
                Vector2 vect = { 0 };

                while ((vectcount += sscanf(cut, "%f%*[,]%f", &vect.x, &vect.y)))
                {
                    if (vectcount % 2 == 0 && vectcount > 0)
                    {
                        cut += COUNTDIGITS(vect.x) + 1 + COUNTDIGITS(vect.y);
                        
                        fldset.field_arr[ind].layer = layer;
                        fldset.field_arr[ind].point_arr.size = vectcount/2 * sizeof(Vector2);
                        fldset.field_arr[ind].point_arr.array = nalloc(fldset.field_arr[ind].point_arr.array, fldset.field_arr[ind].point_arr.size);

                        uint8_t vin = vectcount/2 - 1;
                        ((Vector2*)fldset.field_arr[ind].point_arr.array)[vin] = (Vector2){ vect.x, vect.y };

                        if (cut[0] == ' '){
                            cut++;
                        }
                        else {
                            fldset.field_arr[ind].center = AddCenterToField(&fldset.field_arr[ind]);
                            printf("CENTER:%f, %f\n", fldset.field_arr[ind].center.x, fldset.field_arr[ind].center.y);
                            goto scan_line;
                        }
                    }
                    else { goto scan_line; }
                }
            }
        }
        if (feof(dotfield)) {
            printf("Reached EOF. Fields read: %hhu\n", fldset.fieldcount);
            FREEPTR(line);
            FREEPTR(cut);
        }
        for (int f=0; f < fldset.fieldcount; f++) {
            Field *fld = &fldset.field_arr[f];

            if (fld->point_arr.array != NULL) {
                const size_t length = fld->point_arr.size / sizeof(Vector2);
                float x_arr[length]; float y_arr[length];

                for (int f=0; f < length; f++) {
                    x_arr[f] = ((Vector2*)fld->point_arr.array)[f].x;
                    y_arr[f] = ((Vector2*)fld->point_arr.array)[f].y;
                }

                qsort(x_arr, length, sizeof(float), cmpx);
                qsort(y_arr, length, sizeof(float), cmpy);

                for (int p=0; p < length - 1; p++) {
                    float x_diff = x_arr[p + 1] - x_arr[p];
                    float y_diff = y_arr[p + 1] - y_arr[p];

                    fldset.x_len += x_diff;
                    fldset.y_len += y_diff;
                }
            }
        }
        printf("Lengths: %f %f\n", fldset.x_len, fldset.y_len);
    }
    else {
        perror("FAILED TO OPEN FILE");      
    }
    fclose(dotfield);
    return fldset;
}

Vector2 AddCenterToField(Field *fld) {
    Vector2 vect = { 0, 0 };

    if (fld->point_arr.array != NULL) {
        const size_t length = fld->point_arr.size / sizeof(Vector2);
        float x_arr[length]; float y_arr[length];

        for (int f=0; f < length; f++) {
            x_arr[f] = ((Vector2*)fld->point_arr.array)[f].x;
            y_arr[f] = ((Vector2*)fld->point_arr.array)[f].y;
        }

        qsort(x_arr, length, sizeof(float), cmpx);
        qsort(y_arr, length, sizeof(float), cmpy);

        float cx = x_arr[length-1] - x_arr[0];
        float cy = y_arr[length-1] - y_arr[0];

        vect = (Vector2){ x_arr[0] + cx/2, y_arr[0] + cy/2 };
    }
    return vect;
}