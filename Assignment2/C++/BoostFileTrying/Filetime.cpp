#include <boost/filesystem/operations.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
 
int main( int argc , char *argv[ ] ) {
   if ( argc != 2 ) 
   {
      std::cerr << "Error! Syntax: moditime <filename>!\n" ;
      return 1 ;
   }
   boost::filesystem::path p( argv[1] ) ;
   if ( boost::filesystem::exists( p ) ) 
   {
      std::time_t t = boost::filesystem::last_write_time( p ) ;
      std::cout << "On " << std::ctime( &t ) << " the file " << argv[ 1 ]  << " was modified the last time!\n" ;
      std::ofstream out("time.txt");
      out << t;
      out.close();
      return 0 ;
   } 
   else {
      std::cout << "Could not find file " << argv[ 1 ] << '\n' ;
      return 2 ;
   }
}