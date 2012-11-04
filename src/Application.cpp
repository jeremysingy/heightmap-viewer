#include <Application.h>

#include <iostream>

Application::Application() :
myWindow(sf::VideoMode(800, 600), "Heightmap 3D Viewer")
{
    myWindow.setVerticalSyncEnabled(true);
    myRenderer.onResize(800, 600);
}

void Application::run()
{
    while(myWindow.isOpen())
    {
        // TODO create a separated event manager
        sf::Event event;

        sf::Vector2i mouseDelta;

        while(myWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                myWindow.close();

            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    myWindow.close();

            if(event.type == sf::Event::Resized)
                myRenderer.onResize(event.size.width, event.size.height);

            if(event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i winCenter(myWindow.getSize().x / 2, myWindow.getSize().y / 2);
                
                if(event.mouseMove.x != winCenter.x || event.mouseMove.y != winCenter.y)
                {
                    sf::Mouse::setPosition(winCenter, myWindow);

                    mouseDelta.x = event.mouseMove.x - winCenter.x;
                    mouseDelta.y = event.mouseMove.y - winCenter.y;
                }
            }
        }

        int time = myClock.restart().asMilliseconds();

        // Update and draw the current scene
        // TODO create a scene manager
        myRenderer.updateScene(time, mouseDelta);
        myRenderer.drawScene();

        // Display content
        myWindow.display();
    }
}
