#include <stdio.h>
#include <math.h>

float CaculateRealpoint();
float CaculateTime();
float CaculateCOS();
float CaculateSIN();
float CaculateDeltaZ();

float k = 0.38, k_1 = 0.019;
float s = 5, targetPoint = 0.25, v_0 = 17,
      tempPoint, angle, realPoint, deltaZ;
int iteration_count = 20;

int main()
{
    tempPoint = targetPoint;
    for (int i = 0; i < iteration_count; i++)
    {

        angle = asin(CaculateSIN());
        realPoint = CaculateRealpoint();
        deltaZ = CaculateDeltaZ();
        tempPoint += deltaZ;
        printf("targetPoint%f,realPoint%f,angle%f,deltaZ%f\n", targetPoint, realPoint, angle, deltaZ);
    }
    printf("%f", CaculateRealpoint());
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
