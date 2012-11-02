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
            
            // Vertex coordinates
            Vector3f v1(x, myLoader->valueAt(x, z) * myHeightFactor, z);
            Vector3f v2(myPrecision + x, myLoader->valueAt(myPrecision + x, z) * myHeightFactor, z);
            Vector3f v3(myPrecision + x, myLoader->valueAt(myPrecision + x, myPrecision + z) * myHeightFactor, myPrecision + z);
            Vector3f v4(x, myLoader->valueAt(x, myPrecision + z) * myHeightFactor, myPrecision + z);

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