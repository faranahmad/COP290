#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#define SIZE 100000

bool EqualVector(std::vector<char> file1, std::vector<char> file2)
{
	for(int i=0;i<file1.size();i++)
	{
		if(file1[i]!=file2[i])
		{	
			std::cout<<i<<"    "<<file1[i]<<"    "<<file2[i]<<std::endl;
			return false;
		}
	}
	return true;
}

int main(int argc , char** argv)
{
    std::ifstream ifs1(argv[1],std::ios::binary|std::ios::ate);
    std::ifstream ifs2(argv[2],std::ios::binary|std::ios::ate);

    ifs1.seekg(0, std::ios::end);
    std::ifstream::pos_type pos = ifs1.tellg();
    ifs2.seekg(0, std::ios::end);
    std::ifstream::pos_type pos2 = ifs2.tellg();
    long long counter=0;
    std::vector<char> file1;
    std::vector<char> file2;
    if((long long)pos!=(long long)pos2)
    {
    	std::cout<<"Sizes dont match"<<std::endl;
    	goto WRONG;
    }
    
    while(counter<pos)
    {
    	ifs1.seekg(counter,std::ios::beg);
    	ifs2.seekg(counter,std::ios::beg);
    	if(counter+SIZE>pos)
    	{	
    		int temp=(long long )pos - counter;
    		file1.resize(temp);
    		file2.resize(temp);
    		ifs1.read(&file1[0],temp);
    		ifs2.read(&file2[0],temp);
    	}
    	else
    	{
    		file1.resize(SIZE);
    		file2.resize(SIZE);
    		ifs1.read(&file1[0],SIZE);
    		ifs2.read(&file2[0],SIZE);
    	}
    	std::cout<<file1.size()<<file2.size()<<std::endl;
    	if (EqualVector(file1,file2))
  			std::cout << "success" << std::endl;
  		else
  		{	
  			WRONG:std::cout << "Not equal"<<std::endl;
  			return 1;
  		}
    	counter+=SIZE;
    }
    std::cout<<"Equal"<<std::endl;
    return 0;
}