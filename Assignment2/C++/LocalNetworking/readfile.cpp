#include <iostream>
#include <fstream>
#include <string>
#include <locale>
// #include <codecvt>
#include <fcntl.h>
// #include <io.h>

using namespace std;    // Sorry for this!

void read_all_lines(const wchar_t *filename)
{
    wifstream wifs;
    wstring txtline;
    int c = 0;

    wifs.open(filename);
    if(!wifs.is_open())
    {
        wcerr << L"Unable to open file" << endl;
        return;
    }
    // We are going to read an UTF-8 file
    wifs.imbue(locale(wifs.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));
    while(getline(wifs, txtline))
        wcout << ++c << L'\t' << txtline << L'\n';
    wcout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
    // Console output will be UTF-16 characters
    _setmode(_fileno(stdout), _O_U16TEXT);
    if(argc < 2)
    {
        wcerr << L"Filename expected!" << endl;
        return 1;
    }
    read_all_lines(argv[1]);
    return 0;
}