#include "param.h"
#include "pid.h"
#include "forward.h"

pid pid_velocity;
pid pid_tension;

//����Ϊ Kp Ki Kd ����Ͻ� �������� ���� ȫ�ٻ����� ���ٻ����� �����ͨ�˲�ϵ�� ����ȫ΢��ϵ�� ΢������ϵ��
float pidvelocityparam[11] = { 180.0f, 28.0f, 0.0f, 16000.0f, 40000.0f, 0.0f, 100.0f, 100.0f, 0.8f, 0.0f, 0.0f };
float pidtensionparam[11] = { 180.0f, 28.0f, 0.0f, 16000.0f, 40000.0f, 0.0f, 100.0f, 100.0f, 0.8f, 0.0f, 0.0f };