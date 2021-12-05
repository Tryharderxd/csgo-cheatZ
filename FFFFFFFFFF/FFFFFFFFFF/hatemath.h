#include <math.h>
#include <algorithm>
#include "vector.h"


# define M_PI 3.14159265358979323846

namespace Maths
{
    float FPS(int dwFPS);
    int RNG(int dwArray[]);
    float fRNG(float flMin, float flMax);
    float Hypotenuse(Vector3 vecDelta);
    float Hypotenuse2D(Vector3 vecDelta);
    float ToRadians(float flVal);
    float ToDegree(float flVal);
    float CalculateDistance(Vector3 vecStart, Vector3 vecDestination);
    float FoV(float flFoV);
    float GetDifference(float flFirstAngle, float flSecondAngle);
    int Quadrant(Vector2 vecCoordinate);
    void NormalizeDelta(Vector2 vecCoordinate, Vector2 vecDelta);
    Vector3 CalculateAngle(Vector3 vecSource, Vector3 vecDestination);
    Vector3 ClampAngle(Vector3 vecAngle);
    Vector3 NormalizeAngle(Vector3 vecAngle);
    Vector3 FinalizeAngle(Vector3 vecAngle);
    Vector2 AimAngleToRelatives(Vector3 vecViewAngle, Vector3 vecTargetAngle, float flSensitivity, float flZoomSensitivity, float smo0tie, bool bScoping);
    float CalculateFoV(Vector3 vecLocalPosition, Vector3 vecTargetPosition, Vector3 vecDestination, Vector3 vecViewAngle);
    void NormalizeDelta(Vector2 vecCoordinate, Vector2 vecDelta);
    float CalculateMaxAimValue(float flSensitivity);
}