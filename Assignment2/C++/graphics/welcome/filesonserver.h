#ifndef FILESONSERVER_H
#define FILESONSERVER_H

#include <vector>
#include <string>

class Data
{
    private:
        bool file_or_folder;
        std::string name;
        std::vector<Data> list_of_files;

    public:
        Data();
        Data(std::string);
        Data(std::string, bool);

        std::string GetName();
        std::vector<Data> GetListFiles();

        void SetName(std::string);
        void SetFolder(bool);
        void SetData(std::vector<Data>);

        void InsertData(Data);
        void DeleteData(unsigned int);
        bool IfFileFolder();
};

#endif // FILESONSERVER_H
