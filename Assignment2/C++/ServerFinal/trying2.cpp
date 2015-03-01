#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesonserver.h>

std::vector<string> data;
std::vector<Data> 

int main()
{
	data.push_back("/dude/yo/cool.txt");
	data.push_back("/dude/yo/");
	data.push_back("/dude/yo2/cool.txt");
	data.push_back("/dude/yo2/");
	data.push_back("/dude/yo2/yo3/cool");
	data.push_back("/dude/yo/yo3/");
	data.push_back("/dude/cool.txt");
	data.push_back("/dude/");
	std::vector<string> files;

	std::string mainpath(getenv("HOME"));
	mainpath=mainpath+"/Desktop/DeadDrop/";
	for(int i=0;i<data.size();i++)
	{
		if(data[i][data[i].size()-1]=='/')
		{
			boost::filesystem::path dir(mainpath+data[i]);
            if(!(boost::filesystem::exists(dir)))
            {
                std::cout<<"Directory Doesn't Exists"<<std::endl;
                if (boost::filesystem::create_directories(dir))
                    std::cout << "Directory Successfully Created !" << std::endl;
            }
		}
		else
		{
			files.push_back(data[i]);
		}
	}
	for(int i=0;i<files.size();i++)
	{
		std::ofstream out(mainpath+files[i]);
		string d="DeadDrop";
		out<<DeadDrop;
		out.close();
	}
	return 0;
}