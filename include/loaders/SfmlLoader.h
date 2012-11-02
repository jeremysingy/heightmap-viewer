#ifndef SFMLLOADER_H
#define SFMLLOADER_H

#include <loaders/ILoader.h>
#include <SFML/Graphics/Image.hpp>

class SfmlLoader : public ILoader
{
    public:
        
        SfmlLoader();
        virtual ~SfmlLoader();

        virtual void load(const std::string& filename);
        virtual int valueAt(int x, int y);

    private:

        sf::Image myImage;
};

#endif // SFMLLOADER_H 