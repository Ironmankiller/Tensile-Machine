#include "param.h"
#include "pid.h"
#include "forward.h"

pid pid_velocity;
pid pid_tension;

//依次为 Kp Ki Kd 输出上界 积分上限 死区 全速积分区 变速积分区 输出低通滤波系数 不完全微分系数 微分先行系数
float pidvelocityparam[11] = { 180.0f, 28.0f, 0.0f, 16000.0f, 40000.0f, 0.0f, 100.0f, 100.0f, 0.8f, 0.0f, 0.0f };
float pidtensionparam[11] = { 180.0f, 28.0f, 0.0f, 16000.0f, 40000.0f, 0.0f, 100.0f, 100.0f, 0.8f, 0.0f, 0.0f };