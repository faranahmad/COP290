#include <boost/filesystem.hpp>

int main(int argc, char const* argv[])
{
    boost::filesystem::path dir("/home/skipper/Desktop/yummy/");
    boost::filesystem::create_directory(dir);
    return 0;
}
