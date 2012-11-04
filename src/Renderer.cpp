#include <Renderer.h>
#include <OpenGL.h>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>

const float Renderer::CAM_SPEED = 0.02f;
const float Renderer::CAM_ROT_FACTOR = 0.15f;

Renderer::Renderer() :
myMap("resources/heightmap.png")
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClearDepth(1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    // TODO make the mode change possible at runtime
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::updateScene(int time, sf::Vector2i& mouseDelta)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sf::Vector3f camSpeed = sf::Vector3f();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        camSpeed.z = CAM_SPEED;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        camSpeed.z = -CAM_SPEED;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camSpeed.x = CAM_SPEED;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camSpeed.x = -CAM_SPEED;

    myCamera.move(camSpeed, time);
    myCamera.rotate(mouseDelta.x * CAM_ROT_FACTOR, mouseDelta.y * CAM_ROT_FACTOR);
    myCamera.place();
}

void Renderer::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the axes
    drawAxes();
    
    // Draw the map
    glScalef(0.1f, 0.1f, 0.1f);
    myMap.draw();
}

// Fonction appelée lors du redimensionnement de la fenêtre
void Renderer::onResize(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, width / static_cast<float>(height), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer::drawAxes()
{
    glBegin(GL_LINES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(10.f, 0.f, 0.f);

        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.f, 10.f, 0.f);
        
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.f, 0.f);
        glVertex3f(0.f, 0.f, 10.f);

        glColor3f(1.f, 1.f, 1.f);
    glEnd();
}