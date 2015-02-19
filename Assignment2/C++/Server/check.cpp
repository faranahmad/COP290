#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <unistd.h>
using namespace std;
int main(){
		int part=0;
		std::string p=std::to_string(part);
        std::vector<char>  ans;
        int counter=0;

					while(1)
					{	std::string s="/home/skipper/Desktop/yo/test.txt"+p;
						std::ifstream ifs(s, std::ios::binary|std::ios::ate);
                    	std::cout<<ifs.is_open()<<std::endl;
                    	if(!ifs.is_open())
                    	{
                    		break;
                    	}
                    	std::ifstream::pos_type pos = ifs.tellg();
                    	ans.resize(ans.size()+pos);
                    	ifs.seekg(0, ios::beg);
                    	ifs.read(&ans[counter], pos);
                    	part++;
                    	counter=ans.size();
                    	p=std::to_string(part);
                	}

                	for(int i=0;i<ans.size();i++)
                	{
                		std::cout<<ans[i];
                	}
                }