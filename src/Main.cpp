#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <Application.h>

//////////////////////////////////////////////////
/// Entry point of the application
//////////////////////////////////////////////////
int main()
{
    try
    {
        Application app;
        app.run();
    }
    catch (std::exception ex)
    {
        std::cerr << "Unknown exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}