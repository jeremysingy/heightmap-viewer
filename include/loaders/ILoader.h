#ifndef LOADER_H
#define LOADER_H

#include <string>

class ILoader
{
    public:
        
        ILoader();
        virtual ~ILoader();

        virtual void load(const std::string& filename) = 0;
        virtual int valueAt(int x, int y) = 0;

        unsigned int getWidth() { return myWidth; };
        unsigned int getHeight() { return myHeight; };

    protected:

        unsigned int myWidth;
        unsigned int myHeight;
};

#endif // LOADER_H 