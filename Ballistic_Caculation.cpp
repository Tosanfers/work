#include <stdio.h>
#include <math.h>

float CaculateRealpoint();
float CaculateTime();
float CaculateCOS();
float CaculateSIN();
float CaculateDeltaZ();

float k = 0.038, k_1 = 0.019;
float s = 5, targetPoint = 0.25, v_0 = 17,
      tempPoint, angle, realPoint, deltaZ;
int iteration_count = 20;

int main()
{
    tempPoint = targetPoint;
    for (int i = 0; i < iteration_count; i++)
    {

        realPoint = CaculateRealpoint();
        deltaZ = CaculateDeltaZ();
        tempPoint += deltaZ;
        angle = asin(CaculateSIN());
        // printf("targetPoint%f,realPoint%f,angle%f,deltaZ%f\n", targetPoint, realPoint, angle, deltaZ);
    }
    printf("angle:%f radians   %f degrees", angle, angle / (180.0 / M_PI));
    // angle:0.137424 radians   0.002399 degrees
    // 应有两解，但另一解接近垂直发射，不具有实际应用意义
}

float CaculateRealpoint()
{
    float time = CaculateTime();
    return v_0 * CaculateSIN() * time - 9.8 * time * time / 2;
}
float CaculateTime()
{
    return (exp(k_1 * s) - 1) / (k_1 * v_0 * CaculateCOS());
}
float CaculateCOS()
{
    return s / sqrt(s * s + tempPoint * tempPoint);
}
float CaculateSIN()
{
    return tempPoint / sqrt(s * s + tempPoint * tempPoint);
}
float CaculateDeltaZ()
{
    return targetPoint - realPoint;
}

// https://github.com/Tosanfers/work.git