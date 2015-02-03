#ifndef USER_H
#define USER_H

#include <string>

class User
{
    public:
        User();
        User(std::string);
        User(std::string,std::string);

        std::string GetUserName();
        std::string GetPassword();

        void SetUserName(std::string);
        void SetPassword(std::string);


    private:
        std::string UserName;
        std::string Password;
};

#endif
