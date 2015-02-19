#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
int main(){
boost::filesystem::path dir("/home/skipper/Desktop/yo/");
if(!(boost::filesystem::exists(dir)))
{
    std::cout<<"Doesn't Exists"<<std::endl;
    if (boost::filesystem::create_directory(dir))
        std::cout << "....Successfully Created !" << std::endl;
}
}