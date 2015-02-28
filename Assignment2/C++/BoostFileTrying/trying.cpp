#include "filesonserver.h"
#include <iostream>
#include <vector>

std::string FileName(std::string filename)
{
    std::string ans="";
    int i;
    if(filename[filename.size()-1]=='/')
    {	
    	i=filename.size()-2;
    	ans="/";
    }
    else
    	i=filename.size()-1;
    for(;i>=0;i--)
    {
        if(filename[i]!='/')
            ans=filename[i]+ans;
        else
            break;
    }
    // std::cout<<"FileName returned:"<<ans<<std::endl;
    return ans;
}

std::vector<std::string> files;
std::vector<Data> data;
std::vector<int> length;

void Recurse(std::string name) //name has the complete path
{
	int j=0;
	std::string parent=name.substr(0,name.size()-FileName(name).size()); //path of parent
	std::string parentName=FileName(parent).substr(0,FileName(parent).size()-1); //name of parent
	std::cout<<parent<<'\t'<<parentName<<std::endl;
	Data d;
	if(parentName.size()==0)
	{	
		d=Data(name.substr(1,name.size()-2),true);
		data.push_back(d);
		std::cout<<"Baap created: "<<d.GetName()<<std::endl;
		return;
	}
	std::string s=FileName(name);
	if(s[s.size()-1]=='/')
		d=Data(s.substr(0,s.size()-1),true);
	else
		d=Data(s,false);
	data.push_back(d);
	for(;j<data.size();j++)
	{
		if(parentName.compare(data[j].GetName())==0)
		{	
			std::cout<<"parentName:"<<parentName<<std::endl;
			data[j].InsertData(d);
			std::cout<<"Added1 "<<d.GetName()<<" to "<<data[j].GetName()<<"\n";
			return ;
		}
	}
	Recurse(parent);
	for(j=0;j<data.size();j++)
	{
		if(parentName.compare(data[j].GetName())==0)
		{
			data[j].InsertData(d);
			std::cout<<"Added2 "<<d.GetName()<<" to "<<data[j].GetName()<<"\n";
			return ;
		}
	}
	return;
}

int main()
{
	files.push_back("/dude/yo/cool1.txt");
	files.push_back("/dude/yo/cool2.txt");
	files.push_back("/dude/cool.txt");
	files.push_back("/dude/cool1.txt");
	files.push_back("/dude/cool2.txt");
	files.push_back("/dude/yo2/cool3.txt");
	files.push_back("/dude/yo2/yo3/cool.txt");
	files.push_back("/dude2/yo/cool.txt");
	files.push_back("/dude2/yo/cool.txt");
	files.push_back("/dude2/yocool.txt");

	int total=files.size();
	for(int i=0;i<total;i++)
	{
		std::string name=FileName(files[i]);
		Data d;
		d=Data(name,false);
		std::cout<<"File name:"<<name<<std::endl;
		// std::string parent=files[i].substr(0,files[i].size()-name.size());
		// std::string parentName=FileName(parent).substr(0,FileName(parent).size()-1);
		// std::cout<<"Parent:"<<parent<<'\t'<<parentName<<std::endl;
		Recurse(files[i]);
	}
	for(int i=0;i<data.size();i++)
	{
		Data d=data[i];
		std::cout<<"\n\n\n\n\n"<<"Data name:"<<d.GetName()<<std::endl;
		std:: vector<Data> v=d.GetListFiles();
		for(int j=0;j<v.size();j++)
		{
			std::cout<<v[j].GetName()<<std::endl;
		}
	}
	return 0;
}