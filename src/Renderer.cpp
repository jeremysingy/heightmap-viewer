#include <Renderer.h>
#include <OpenGL.h>

#include <iostream>

Renderer::Renderer() :
myMap("resources/heightmap.png"),
myAngle(0.f)
{
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClearDepth(1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 800.0f / 600.0f, 1.0, 100.0);

    // TODO make the mode change possible at runtime
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::drawScene(int time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(0.0, 0.0, -50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(-10.0, 2.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Rotation
    /*myAngle += 0.05f * time;
    if(myAngle >= 360.f)
        myAngle = 0.f;

    glRotatef(myAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(myAngle * 2, 0.0f, 0.0f, 1.0f);*/

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
    glEnd();
    
    glColor3f(1.f, 1.f, 1.f);
    
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