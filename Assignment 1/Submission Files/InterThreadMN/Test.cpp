#include <iostream>
#include "Test.h"

Test::Test(std::string description)
{
    this->description = description;
    verbose = true;
    isPass = true;
}

Test::~Test()
{
    if(verbose)
    {
        PrintPassFail(isPass);
        std::cout<<description<<std::endl;
    }
}
void Test::VerifyTrue(bool value, std::string testDescription)
{
    if(!value)
    {
        PrintPassFail(value);
        std::cout<<testDescription<<std::endl;
        isPass = false;
    }
}

void Test::PrintPassFail(bool pass)
{
    if(!pass)
    {
        std::cout<<"Fail: ";
    }
    else
    {
        std::cout<<"Pass: ";
    }
}

bool Test::isPassed()
{
    return isPass;
}
