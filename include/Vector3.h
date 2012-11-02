#ifndef VECTOR3_H
#define VECTOR3_H

#include <SFML/Graphics.hpp>
#include <Renderer.h>

template <typename T>
class Vector3
{
    public:
        
        Vector3();
        Vector3(float x, float y, float z);

        T X;
        T Y;
        T Z;
};

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

#include <Vector3.inl>

#endif // VECTOR3_H 