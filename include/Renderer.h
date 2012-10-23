#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
    public:
        
        Renderer();
        void drawScene(int time);
        void onResize(unsigned int width, unsigned int height);

    private:

        float myAngle;
};

#endif // RENDERER_H 