#include <Map.h>
#include <loaders/SfmlLoader.h>
#include <SFML/System/Vector3.hpp>
#include <OpenGL.h>

Map::Map(const std::string& filename) :
myLoader(new SfmlLoader),    // TODO use a real factory or media manager (more flexibility)
myPrecision(5),
myHeightFactor(0.2f)    // TODO no default values
{
    myLoader->load(filename);
    compile();
}

void Map::compile()
{
    myList = glGenLists(1);

    glNewList(myList, GL_COMPILE);

    glBegin(GL_TRIANGLES);

    // For each row
    for(unsigned int x = 0; x < myLoader->getHeight() - myPrecision; x += myPrecision)
    {
        // For each column
        for(unsigned int z = 0; z < myLoader->getWidth() - myPrecision; z += myPrecision)
        {
            // vertex1(x, getPixel(x, z), z, x / getWidth(), 1.f - (z / getHeight()) );
            // vertex2(myPrecision + x, getPixel(myPrecision + x, z), z, (x + myPrecision) / getWidth(), 1.f - (z / getHeight()) );
            // vertex3(myPrecision + x, getPixel(myPrecision + x, myPrecision + z), myPrecision + z, (x + myPrecision) / getWidth(), 1.f - ((z + myPrecision) / getHeight()) );
            // vertex4(x, getPixel(x, myPrecision + z), myPrecision + z, x / static_cast<float>(getWidth()), 1.f - ((z + myPrecision) / getHeight()) );
            
            float xVal = static_cast<float>(x);
            float zVal = static_cast<float>(z);

            // Vertex coordinates
            sf::Vector3f v1(xVal, myLoader->valueAt(x, z) * myHeightFactor, zVal);
            sf::Vector3f v2(myPrecision + xVal, myLoader->valueAt(myPrecision + x, z) * myHeightFactor, zVal);
            sf::Vector3f v3(myPrecision + xVal, myLoader->valueAt(myPrecision + x, myPrecision + z) * myHeightFactor, myPrecision + zVal);
            sf::Vector3f v4(xVal, myLoader->valueAt(x, myPrecision + z) * myHeightFactor, myPrecision + zVal);

            // First triangle
            glVertex3f(v3.x, v3.y, v3.z);
            glVertex3f(v2.x, v2.y, v2.z);
            glVertex3f(v1.x, v1.y, v1.z);

            // Second triangle
            glVertex3f(v4.x, v4.y, v4.z);
            glVertex3f(v3.x, v3.y, v3.z);
            glVertex3f(v1.x, v1.y, v1.z);
        }
    }
    
    glEnd();

    glEndList();
}

void Map::draw()
{
    glCallList(myList);
}