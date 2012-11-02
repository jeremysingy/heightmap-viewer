#include <Application.h>

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

        while(myWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                myWindow.close();

            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    myWindow.close();

            if(event.type == sf::Event::Resized)
                myRenderer.onResize(event.size.width, event.size.height);
        }

        int time = myClock.restart().asMilliseconds();

        // Draw the current scene
        // TODO create a scene manager
        myRenderer.drawScene(time);

        // Display content
        myWindow.display();
    }
}
