//  filesystem tut2.cpp  ---------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
using namespace std;
using namespace boost::filesystem;

path databaseDir ("/home/skipper/Desktop/Dropbox/COP290/Assignment2/Database/");
path users ("/home/skipper/Desktop/Dropbox/COP290/Assignment2/Users/");

void transfer_file( const path & dir_path,         // in this directory
                path & destination_path )            // placing path here if found
{
  directory_iterator end_itr; // default construction yields past-the-end
  for ( directory_iterator itr( dir_path );itr != end_itr; ++itr )
  {
    path current(itr->path());
    if ( is_directory(itr->status()) )
    {
      string newDest=destination_path.string()+current.filename().string()+"/";
      path newDestPath (newDest);
      if(!exists(newDestPath))
      {
        create_directory(newDestPath);
      }
      transfer_file( current, newDestPath );
    }
    else 
    {
      string newDest=destination_path.string()+current.filename().string();
      path newDestPath (newDest);
      if(!exists(newDestPath))
      {
        copy_file(current,newDestPath,copy_option::overwrite_if_exists);
      }
    }
  }
}

int main(int argc, char* argv[])
{
  if (!exists(databaseDir))    // Creating the database directory if it does not exist
  {
      create_directory(databaseDir);
  }
  if(!exists(users))    // Creating the users directory if it does not exit
  {
      create_directory(users);
  }
  string pth=users.string() + argv[1] + "/";
  path p (pth);
  if(!exists(p)) // Checking if the user is in the system
  {
      cout<<"User not found!"<<endl;
  }
  else
  {
    transfer_file(p,databaseDir); // Copying contents
  }
  return 0;
}
