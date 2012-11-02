#include <loaders/SfmlLoader.h>
#include <exceptions/LoadingException.h>

SfmlLoader::SfmlLoader()
{

}

SfmlLoader::~SfmlLoader()
{

}

void SfmlLoader::load(const std::string& filename)
{
    if(!myImage.loadFromFile(filename))
        throw LoadingException("Unable to load file '" + filename + "'");

    myWidth = myImage.getSize().x;
    myHeight = myImage.getSize().y;
}

int SfmlLoader::valueAt(int x, int y)
{
    return myImage.getPixel(x, y).r;
}