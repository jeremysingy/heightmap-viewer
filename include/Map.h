#ifndef MAP_H
#define MAP_H

#include <loaders/ILoader.h>

#include <string>
#include <memory>
#include <SFML/Graphics/Image.hpp>

class Map
{
    public:
        
        Map(const std::string& filename, const std::string& textureName = "");
        void draw();

    private:

        void compile();

        std::unique_ptr<ILoader> myLoader;
        sf::Image myTextureImg;

        int myList;
        int myPrecision;
        float myHeightFactor;
        unsigned int myTexture;
};

#endif // MAP_H 