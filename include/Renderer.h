#ifndef RENDERER_H
#define RENDERER_H

#include <Map.h>
#include <Camera.h>

#include <SFML/System/Vector2.hpp>

class Renderer
{
    public:

        static const float CAM_SPEED;
        static const float CAM_ROT_FACTOR;
        
        Renderer();
        
        void updateScene(int time, sf::Vector2i& mouseDelta);
        void drawScene();
        void onResize(unsigned int width, unsigned int height);

    private:

        void drawAxes();

        Map myMap;
        Camera myCamera;
};

#endif // RENDERER_H 