#ifndef MAP_H
#define MAP_H

#include <string>
#include <memory>
#include <loaders/ILoader.h>

//class ILoader;

class Map
{
    public:
        
        Map(const std::string& filename);
        void draw();

    private:

        void compile();

        std::unique_ptr<ILoader> myLoader;
        int myList;
        int myPrecision;
        float myHeightFactor;
};

#endif // MAP_H 