#include <Map.h>
#include <loaders/SfmlLoader.h>
#include <Vector3.h>
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
            Vector3f v1(xVal, myLoader->valueAt(x, z) * myHeightFactor, zVal);
            Vector3f v2(myPrecision + xVal, myLoader->valueAt(myPrecision + x, z) * myHeightFactor, zVal);
            Vector3f v3(myPrecision + xVal, myLoader->valueAt(myPrecision + x, myPrecision + z) * myHeightFactor, myPrecision + zVal);
            Vector3f v4(xVal, myLoader->valueAt(x, myPrecision + z) * myHeightFactor, myPrecision + zVal);

            // First triangle
            glVertex3f(v3.X, v3.Y, v3.Z);
            glVertex3f(v2.X, v2.Y, v2.Z);
            glVertex3f(v1.X, v1.Y, v1.Z);

            // Second triangle
            glVertex3f(v4.X, v4.Y, v4.Z);
            glVertex3f(v3.X, v3.Y, v3.Z);
            glVertex3f(v1.X, v1.Y, v1.Z);
        }
    }
    
    glEnd();

    glEndList();
}

void Map::draw()
{
    glCallList(myList);
}