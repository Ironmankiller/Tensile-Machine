#include "Tensile.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "BSP\ESCON\ESCON.h"
#include "BSP\ADS1255\ADS1255.h"
#include "BSP\Time\Time.h"

sTensile_Typedef Tensile;     //小车信息

void Tensile_Init(void){
    memset(&Tensile,0,sizeof(sTensile_Typedef));
    
    Tensile.LVDT.offset_velocity = 0;
    Tensile.LVDT.output_max = 4;
    Tensile.LVDT.output_min = 0;
    Tensile.LVDT.range = 5;
    
    Tensile.TensionSensor.offset_tension = 0;
    Tensile.TensionSensor.output_max = 4;
    Tensile.TensionSensor.output_min = 0;
    Tensile.TensionSensor.range = 1500;
    
    
    Tensile.state = Stop;
    Tensile.mode = CVelocity;                  //默认恒速状态运行
}

void Tensile_Calibrate(void){
    Tensile.LVDT.offset_velocity -= Tensile.LVDT.velocity;
    Tensile.TensionSensor.offset_tension -= Tensile.TensionSensor.tension;
}

void Tensile_Read_LVDT(void) {
    
    double output;
    double cycle_time = Get_Cycle_T(2);
    static double last_position = 0;
    output = ReadASingleData(0x01,0x00);
    Tensile.LVDT.position = Tensile.LVDT.range * output / (Tensile.LVDT.output_max - Tensile.LVDT.output_min);
    Tensile.LVDT.velocity = (Tensile.LVDT.position - last_position)/cycle_time;
}

void Tensile_Read_TensionSensor(void) {

}
