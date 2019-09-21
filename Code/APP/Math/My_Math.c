#include "My_Math.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


/********************************
 *函数名：myatoi
 *作用：将字符串转换为整型数
 *参数：字符串指针
 *返回值：整型数
 ********************************/
int myatoi(char *str)
{
    int num;
    num=atoi(str);
    return num;
}


char *myitoa(int value, char *string, int radix)
{                                        
    int     i, d;
    int     flag = 0;
    char    *ptr = string;
 
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
 
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
 
    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';
 
        /* Make the value positive. */
        value *= -1;
    }
 
    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
 
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
 
    /* Null terminate the string. */
    *ptr = 0;
 
    return string;
 
} /* NCL_Itoa */

/********************************
 *函数名：string_to_float
 *作用：字符串转换成浮点数
 *参数：str
 *返回值：浮点数
 ********************************/
float string_to_float(u8 *str)
{
     u8 i,j,k,negative=0;
    #define s_temp str
    float result=0,result_1=0;
    for(i=0;i<10;i++)
    {
         j=str[i];
        if(j==0||((j<'0'||j>'9')&&(j!='.')&&(j!='-')))break;             
    } 
    k=j=i;//数值的个数
    for(i=0;i<j;i++)//查找小数点的位置，结束后小数点位于第i+1位
    {
         if(s_temp[i]=='.')break;         
    }
    
    for(j=0;j<i;j++)
    {
         if(s_temp[j]=='-')     {negative=1;continue;}        
         result=result*10+(s_temp[j]-'0');            
    }
    j++;//加1后j=i+1，即小数点的位置
    i=j;//第一个小数的位置
    for(;j<k;j++)
    {
         if(s_temp[j]<'0'||s_temp[j]>'9')break;//非法字符，返回
        result_1=result_1*10+(s_temp[j]-'0');      
    }
    for(j=0;j<(k-i);j++)result_1*=0.1f;
    result+=result_1;
    
    if(negative)result=-result;
    return result;
}

/********************************
 *函数名：swap
 *作用：交换两个数的值
 *参数：交换的两个数
 *返回值：无
 ********************************/
void swap(int *a, int *b)  
{
    int temp;
 
    temp = *a;
    *a = *b;
    *b = temp;
 
    return ;
}
 
/************************************
 *函数名：quicksort
 *作用：快速排序算法
 *参数：排序数组，开始结束索引
 *返回值：无
 ************************************/
void quicksort(int array[], int begin, int end)
{
    int i, j;
 
    if(begin < end)
    {
        i = begin + 1;
        j = end;
          
        while(i < j)
        {
            if(array[i] > array[begin])
            {
                swap(&array[i], &array[j]); 
                j--;
            }
            else
            {
                i++; 
            }
        }
 
        if(array[i] >= array[begin])  // 这里必须要取等“>=”，否则数组元素由相同的值时，会出现错误！
        {
            i--;
        }
 
        swap(&array[begin], &array[i]);
        
        quicksort(array, begin, i);
        quicksort(array, j, end);
    }
}

void Bubble_Sort(uint32_t _data[], uint32_t size)
{
    int i = 0;
    int j = 0;
    uint16_t temp = 0;
    for (j = 0; j < size; j++)
    {
        for (i = size - 1; i > j; i--)
        {
            if (_data[j] < _data[i])
            {
                temp = _data[j];
                _data[j] = _data[i];
                _data[i] = temp;
            }
        }
    }
}

const static float fast_atan_table[257] =
{
    0.000000e+00, 3.921549e-03, 7.842976e-03, 1.176416e-02,
    1.568499e-02, 1.960533e-02, 2.352507e-02, 2.744409e-02,
    3.136226e-02, 3.527947e-02, 3.919560e-02, 4.311053e-02,
    4.702413e-02, 5.093629e-02, 5.484690e-02, 5.875582e-02,
    6.266295e-02, 6.656816e-02, 7.047134e-02, 7.437238e-02,
    7.827114e-02, 8.216752e-02, 8.606141e-02, 8.995267e-02,
    9.384121e-02, 9.772691e-02, 1.016096e-01, 1.054893e-01,
    1.093658e-01, 1.132390e-01, 1.171087e-01, 1.209750e-01,
    1.248376e-01, 1.286965e-01, 1.325515e-01, 1.364026e-01,
    1.402496e-01, 1.440924e-01, 1.479310e-01, 1.517652e-01,
    1.555948e-01, 1.594199e-01, 1.632403e-01, 1.670559e-01,
    1.708665e-01, 1.746722e-01, 1.784728e-01, 1.822681e-01,
    1.860582e-01, 1.898428e-01, 1.936220e-01, 1.973956e-01,
    2.011634e-01, 2.049255e-01, 2.086818e-01, 2.124320e-01,
    2.161762e-01, 2.199143e-01, 2.236461e-01, 2.273716e-01,
    2.310907e-01, 2.348033e-01, 2.385093e-01, 2.422086e-01,
    2.459012e-01, 2.495869e-01, 2.532658e-01, 2.569376e-01,
    2.606024e-01, 2.642600e-01, 2.679104e-01, 2.715535e-01,
    2.751892e-01, 2.788175e-01, 2.824383e-01, 2.860514e-01,
    2.896569e-01, 2.932547e-01, 2.968447e-01, 3.004268e-01,
    3.040009e-01, 3.075671e-01, 3.111252e-01, 3.146752e-01,
    3.182170e-01, 3.217506e-01, 3.252758e-01, 3.287927e-01,
    3.323012e-01, 3.358012e-01, 3.392926e-01, 3.427755e-01,
    3.462497e-01, 3.497153e-01, 3.531721e-01, 3.566201e-01,
    3.600593e-01, 3.634896e-01, 3.669110e-01, 3.703234e-01,
    3.737268e-01, 3.771211e-01, 3.805064e-01, 3.838825e-01,
    3.872494e-01, 3.906070e-01, 3.939555e-01, 3.972946e-01,
    4.006244e-01, 4.039448e-01, 4.072558e-01, 4.105574e-01,
    4.138496e-01, 4.171322e-01, 4.204054e-01, 4.236689e-01,
    4.269229e-01, 4.301673e-01, 4.334021e-01, 4.366272e-01,
    4.398426e-01, 4.430483e-01, 4.462443e-01, 4.494306e-01,
    4.526070e-01, 4.557738e-01, 4.589307e-01, 4.620778e-01,
    4.652150e-01, 4.683424e-01, 4.714600e-01, 4.745676e-01,
    4.776654e-01, 4.807532e-01, 4.838312e-01, 4.868992e-01,
    4.899573e-01, 4.930055e-01, 4.960437e-01, 4.990719e-01,
    5.020902e-01, 5.050985e-01, 5.080968e-01, 5.110852e-01,
    5.140636e-01, 5.170320e-01, 5.199904e-01, 5.229388e-01,
    5.258772e-01, 5.288056e-01, 5.317241e-01, 5.346325e-01,
    5.375310e-01, 5.404195e-01, 5.432980e-01, 5.461666e-01,
    5.490251e-01, 5.518738e-01, 5.547124e-01, 5.575411e-01,
    5.603599e-01, 5.631687e-01, 5.659676e-01, 5.687566e-01,
    5.715357e-01, 5.743048e-01, 5.770641e-01, 5.798135e-01,
    5.825531e-01, 5.852828e-01, 5.880026e-01, 5.907126e-01,
    5.934128e-01, 5.961032e-01, 5.987839e-01, 6.014547e-01,
    6.041158e-01, 6.067672e-01, 6.094088e-01, 6.120407e-01,
    6.146630e-01, 6.172755e-01, 6.198784e-01, 6.224717e-01,
    6.250554e-01, 6.276294e-01, 6.301939e-01, 6.327488e-01,
    6.352942e-01, 6.378301e-01, 6.403565e-01, 6.428734e-01,
    6.453808e-01, 6.478788e-01, 6.503674e-01, 6.528466e-01,
    6.553165e-01, 6.577770e-01, 6.602282e-01, 6.626701e-01,
    6.651027e-01, 6.675261e-01, 6.699402e-01, 6.723452e-01,
    6.747409e-01, 6.771276e-01, 6.795051e-01, 6.818735e-01,
    6.842328e-01, 6.865831e-01, 6.889244e-01, 6.912567e-01,
    6.935800e-01, 6.958943e-01, 6.981998e-01, 7.004964e-01,
    7.027841e-01, 7.050630e-01, 7.073330e-01, 7.095943e-01,
    7.118469e-01, 7.140907e-01, 7.163258e-01, 7.185523e-01,
    7.207701e-01, 7.229794e-01, 7.251800e-01, 7.273721e-01,
    7.295557e-01, 7.317307e-01, 7.338974e-01, 7.360555e-01,
    7.382053e-01, 7.403467e-01, 7.424797e-01, 7.446045e-01,
    7.467209e-01, 7.488291e-01, 7.509291e-01, 7.530208e-01,
    7.551044e-01, 7.571798e-01, 7.592472e-01, 7.613064e-01,
    7.633576e-01, 7.654008e-01, 7.674360e-01, 7.694633e-01,
    7.714826e-01, 7.734940e-01, 7.754975e-01, 7.774932e-01,
    7.794811e-01, 7.814612e-01, 7.834335e-01, 7.853983e-01,
    7.853983e-01
};


#define TAN_MAP_SIZE    256
#define TAN_MAP_RES     0.003921569f     /* (smallest non-zero value in table) */
float fast_atan2(float y, float x)
{
    float x_abs, y_abs, z;
    float alpha, angle, base_angle;
    int index;

    /* don't divide by zero! */
    if ((y == 0.0f) && (x == 0.0f))
        angle = 0.0f;
    else
    {
        /* normalize to +/- 45 degree range */
        y_abs = my_abs(y);
        x_abs = my_abs(x);
        //z = (y_abs < x_abs ? y_abs / x_abs : x_abs / y_abs);
        if (y_abs < x_abs)
            z = y_abs / x_abs;
        else
            z = x_abs / y_abs;
        /* when ratio approaches the table resolution, the angle is */
        /*      best approximated with the argument itself...       */
        if (z < TAN_MAP_RES)
            base_angle = z;
        else
        {
            /* find index and interpolation value */
            alpha = z * (float)TAN_MAP_SIZE - .5f;
            index = (int)alpha;
            alpha -= (float)index;
            /* determine base angle based on quadrant and */
            /* add or subtract table value from base angle based on quadrant */
            base_angle = fast_atan_table[index];
            base_angle += (fast_atan_table[index + 1] - fast_atan_table[index]) * alpha;
        }

        if (x_abs > y_abs)
        {        /* -45 -> 45 or 135 -> 225 */
            if (x >= 0.0f)
            {           /* -45 -> 45 */
                if (y >= 0.0f)
                    angle = base_angle;   /* 0 -> 45, angle OK */
                else
                    angle = -base_angle;  /* -45 -> 0, angle = -angle */
            }
            else
            {                  /* 135 -> 180 or 180 -> -135 */
                angle = 3.14159265358979323846;

                if (y >= 0.0f)
                    angle -= base_angle;  /* 135 -> 180, angle = 180 - angle */
                else
                    angle = base_angle - angle;   /* 180 -> -135, angle = angle - 180 */
            }
        }
        else
        {                    /* 45 -> 135 or -135 -> -45 */
            if (y >= 0.0f)
            {           /* 45 -> 135 */
                angle = 1.57079632679489661923;

                if (x >= 0.0f)
                    angle -= base_angle;  /* 45 -> 90, angle = 90 - angle */
                else
                    angle += base_angle;  /* 90 -> 135, angle = 90 + angle */
            }
            else
            {                  /* -135 -> -45 */
                angle = -1.57079632679489661923;

                if (x >= 0.0f)
                    angle += base_angle;  /* -90 -> -45, angle = -90 + angle */
                else
                    angle -= base_angle;  /* -135 -> -90, angle = -90 - angle */
            }
        }
    }


#ifdef ZERO_TO_TWOPI
    if (angle < 0)
        return (angle + TWOPI);
    else
        return (angle);
#else
    return (angle);
#endif
}

float To_180_degrees(float x)
{
    return (x>180 ? (x - 360) : (x<-180 ? (x + 360) : x));
}


/**************************实现函数********************************************
*函数原型:  float invSqrt(float x)
*功　　能:  Fast inverse square-root. 1/Sqrt(x)
*输入参数： 要计算的值
*输出参数： 结果
*******************************************************************************/
float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}



