#include <Map.h>
#include <OpenGL.h>
#include <loaders/SfmlLoader.h>
#include <exceptions/LoadingException.h>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector3.hpp>

Map::Map(const std::string& filename, const std::string& textureName) :
myLoader(new SfmlLoader),    // TODO use a real factory or media manager (more flexibility)
myPrecision(5),
myHeightFactor(0.2f),   // TODO no default values
myTexture(0)
{
    myLoader->load(filename);

    // TODO create a class handling OpenGL textures
    if(!textureName.empty())
    {
        if (!myTextureImg.loadFromFile(textureName))
            throw LoadingException("Unable to load file '" + textureName + "'");
    }

    compile();
}

void Map::compile()
{
    // Temporary: to test if the image was loaded...
    if(myTextureImg.getSize().x > 0)
    {
        glGenTextures(1, &myTexture);
        glBindTexture(GL_TEXTURE_2D, myTexture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, myTextureImg.getSize().x, myTextureImg.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, myTextureImg.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, myTexture);
    glColor4f(1.f, 1.f, 1.f, 1.f);

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

            // Texture coordinates
            sf::Vector2f t1(xVal / myLoader->getWidth(), 1.f - zVal / myLoader->getHeight());
            sf::Vector2f t2((xVal + myPrecision) / myLoader->getWidth(), 1.f - zVal / myLoader->getHeight());
            sf::Vector2f t3((xVal + myPrecision) / myLoader->getWidth(), 1.f - (zVal + myPrecision) / myLoader->getHeight());
            sf::Vector2f t4(xVal / myLoader->getWidth(), 1.f - (zVal + myPrecision) / myLoader->getHeight());

            // First triangle
            glTexCoord2f(t3.x, t3.y);
            glVertex3f(v3.x, v3.y, v3.z);
            glTexCoord2f(t2.x, t2.y);
            glVertex3f(v2.x, v2.y, v2.z);
            glTexCoord2f(t1.x, t1.y);
            glVertex3f(v1.x, v1.y, v1.z);

            // Second triangle
            glTexCoord2f(t4.x, t4.y);
            glVertex3f(v4.x, v4.y, v4.z);
            glTexCoord2f(t3.x, t3.y);
            glVertex3f(v3.x, v3.y, v3.z);
            glTexCoord2f(t1.x, t1.y);
            glVertex3f(v1.x, v1.y, v1.z);
        }
    }
    
    glEnd();

    glEndList();
}

void Map::draw()
{
    glEnable(GL_TEXTURE_2D);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glCallList(myList);

    glDisable(GL_TEXTURE_2D);
}