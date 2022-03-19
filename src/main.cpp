#include <exception>
#include <iostream>

#include "App.h"

int main()
{
    std::unique_ptr<App> app;
    std::make_unique<App>();

    try
    {
       app->Run();
    }
    catch( const std::exception& e )
    {
        std::cout << e.what() << '\n';
    }

    return 0;   
}