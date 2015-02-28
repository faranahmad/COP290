#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "filesonserver.h"

std::vector<std::string> data;

std::string GetUserName(std::string name)
{
	std::string ans;
	int i=0;
	int it=0;
	while(i<3)
	{
		ans=ans+name[it];
		if(name[it]=='/')
			i++;
		it++;
	}
	std::cout<<name<<"\t"<<ans<<std::endl;
	return ans;
}

std::vector<Data> GetDataFiles(std::string location)
{
	boost::filesystem::path p (location);
	std::vector< Data > ans;		
	if (exists(p))    // does p actually exist?
	{
		std::vector<boost::filesystem::path> v;
        std::copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(), back_inserter(v));
        std::sort(v.begin(), v.end());
        for (int i=0; i<v.size() ; i++ )
        {
        	if (is_regular_file(v[i]))
        	{
	        	ans.push_back(Data(v[i].string(),false));
        	}
        	else
        	{
        		Data d=Data(v[i].string(),true);
        		d.SetData(GetDataFiles(v[i].string()));
        		ans.push_back(d);
        	};
        }
    }
    else
    {
	   	std::cout <<"folder/file:"<<location<<" DNE \n";	 	
    }
    return ans;

}

void Display(std::vector<Data> v)
{
	for(int i=0;i<v.size();i++)
	{
		std::cout<<"Data name:"<<v[i].GetName()<<std::endl;
		Display(v[i].GetListFiles());
	}
	return;
}

int main() // "/username/.temp/..."
{
	data.push_back("/dude/.temp/yo/cool.txt");
	data.push_back("/dude/.temp/yo/");
	data.push_back("/dude/.temp/yo2/cool.txt");
	data.push_back("/dude/.temp/yo2/");
	data.push_back("/dude/.temp/yo2/yo3/cool");
	data.push_back("/dude/.temp/yo2/yo3/");
	data.push_back("/dude/.temp/cool.txt");
	data.push_back("/dude/");
	std::vector<std::string> files;

	std::string mainpath(getenv("HOME"));
	mainpath=mainpath+"/Desktop/DeadDrop/";
	for(int i=0;i<data.size();i++)
	{
		if(data[i][data[i].size()-1]=='/')
		{
			boost::filesystem::path dir((mainpath+data[i]).c_str());
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
		std::cout<<mainpath+files[i]<<std::endl;
		std::ofstream out((mainpath+files[i]).c_str());
		std::string d="DeadDrop";
		out<<d;
		std::cout<<"Written\n";
		out.close();
	}

	std::string location=mainpath+GetUserName(data[0]);
	
	std::cout<<mainpath+GetUserName(data[0])<<std::endl;
	boost::filesystem::path directory_path((mainpath+GetUserName(data[0])).c_str());

	std::vector<Data> v=GetDataFiles(location);

	Display(v);

	if(boost::filesystem::exists(directory_path))
	{
   		boost::filesystem::remove_all(directory_path);
	}
	return 0;
}