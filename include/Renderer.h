#ifndef RENDERER_H
#define RENDERER_H

#include <Map.h>
#include <loaders/SfmlLoader.h>

class Renderer
{
    public:
        
        Renderer();
        void drawScene(int time);
        void onResize(unsigned int width, unsigned int height);

    private:

        Map/*<SfmlLoader>*/ myMap;
        float myAngle;
};

#endif // RENDERER_H 