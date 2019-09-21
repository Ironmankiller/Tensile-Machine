#include "Tensile.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "BSP\ESCON\ESCON.h"

sTensile_Typedef Tensile;     //С����Ϣ

void Tensile_Init(void){
    memset(&Tensile,0,sizeof(sTensile_Typedef));
    Tensile.offset_velocity = 0;
    Tensile.offset_strength = 0;
    Tensile.state = Stop;
    Tensile.mode = CVelocity;                  //Ĭ�Ϻ���״̬����
}

void Tensile_Param_Update(float velocity, float strength){
    Tensile.velocity = velocity + Tensile.offset_velocity;
    Tensile.strength = strength + Tensile.offset_strength;
}

void Tensile_Calibrate(void){
    Tensile.offset_velocity -= Tensile.velocity;
    Tensile.offset_strength -= Tensile.strength;
}

