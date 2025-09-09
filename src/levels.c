#include <stdio.h>
#include <lslread.h>
#include "levels.h"

LSL_Layout PAX_Congress;
LSL_Texture_Container PAX_Container_01;
TrajLayout PAX_Trajectory_01;

LSL_Layout * current_level;
LSL_Texture_Container * current_tex_cont;
TrajLayout * current_traject;


void LoadLevels(void) {
    PAX_Congress = ReadMap("assets/levels/PAX_Congress.lsl");

    current_level = &PAX_Congress;
}

void LoadTextureContainers(void) {
    CreateLSLTexCont(PAX_Container_01, PAX_Congress);

    current_tex_cont = &PAX_Container_01;
}

void LoadTrajectories(void) {
    PAX_Trajectory_01 = LoadTrajFile("assets/levels/PAX_Congress.traj");

    current_traject = &PAX_Trajectory_01;

    for (int i=0; i < 16; i++) {
        printf("Count: %hu \n", (*current_traject)[i].count);
        for (int l=0; l < (*current_traject)[i].count; l++) {
            printf("Layer:[%hu] %f,%f \n", i, (*current_traject)[i].vect_arr[l].x, (*current_traject)[i].vect_arr[l].y);
        }
    }
}