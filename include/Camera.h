#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/System/Vector3.hpp>

class Camera
{
    public:
        
        Camera();
        void move(const sf::Vector3f& speed, int elapsedTime);
        void rotate(float horizontal, float vertical);
        void place();

    private:

        float myHorizontalAngle;
        float myVerticalAngle;

        sf::Vector3f myPosition;
        sf::Vector3f myDeltaPos;

        //float myDistance;
};

#endif // CAMERA_H 