#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static std::vector<char> ReadAllBytes(char const* filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

int main(int argc, char* argv[])
{
	std::vector<char> ans = ReadAllBytes(argv[1]);
	std::string data="";
	for (int i=0; i<ans.size() ; i++ )
	{
		data+=ans[i];
	}
	std::ofstream out("Anu2.wav");
	out << data;
	out.close();
	return 0;
}