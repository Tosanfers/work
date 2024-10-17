    for (int i = 0; i < iteration_count; i++)
    {
        tempPoint = targetPoint;
        angle = asin(CaculateSIN());
        realPoint = CaculateRealpoint();
        deltaZ = CaculateDeltaZ();
        tempPoint += deltaZ;
        printf("targetPoint%f,realPoint%f,angle%f,deltaZ%f\n", targetPoint, realPoint, angle, deltaZ);
    }