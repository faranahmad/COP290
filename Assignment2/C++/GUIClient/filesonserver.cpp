#include "filesonserver.h"

Data::Data()
{
    name = "";
    list_of_files = std::vector<Data>();
    file_or_folder = false;
}

Data::Data(std::string x)
{
    name  = x;
    list_of_files = std::vector<Data>();
    file_or_folder = false;
}

Data::Data(std::string x, bool y)
{
    name = x;
    file_or_folder = y;
    list_of_files = std::vector<Data>();
}

std::string Data::GetName()
{
    return name;
}

std::vector<Data> Data::GetListFiles()
{
    return list_of_files;
}

bool Data::IfFileFolder()
{
    return file_or_folder;
}
void Data::SetName(std::string x)
{
    name = x;
}

void Data::SetFolder(bool x)
{
    file_or_folder = x;
}
void Data::InsertData(Data y)
{
    list_of_files.push_back(y);
}

void Data::SetData(std::vector<Data> y)
{
    list_of_files = y;
}

void Data::DeleteData(unsigned int x)
{
    if (x < list_of_files.size())
    {
        list_of_files.erase(list_of_files.begin()+x);
    }
}
