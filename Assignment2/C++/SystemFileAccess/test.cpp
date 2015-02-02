#include <boost/filesystem.hpp>
#include <string>
using namespace boost::filesystem;
using namespace std;


path databaseDir ("/home/skipper/Desktop/Dropbox/COP290/Assignment2/Database");
int main(int argc, char* argv[])
{
  path p (argv[1]);   // p reads clearer than argv[1] in the following code

  if (exists(p))    // does p actually exist?
  {
    if (is_regular_file(p))        // is p a regular file?   
      cout << p << " size is " << file_size(p) << '\n';

    else if (is_directory(p))      // is p a directory?
      cout << p << "is a directory\n";

    else
      cout << p << "exists, but is neither a regular file nor a directory\n";
  }
  else
    cout << p << "does not exist\n";

  return 0;
}