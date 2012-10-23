#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <Renderer.h>

class Application
{
    public:
        
        Application();
        void run();

    private:

        sf::Window myWindow;
        sf::Clock  myClock;
        Renderer   myRenderer;
};

#endif // APPLICATION_H 