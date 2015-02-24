#include "UserBaseTests.h"

bool RunAllUserBaseTests()
{
	UserBaseInitialisationTests();
}

bool UserBaseInitialisationTests()
{
	Test t("Testing initialisation of user base");
	UserBase u;	
	t.VerifyTrue(u.GetNumberOfUsers()==0,"number of users should be 0");
	
}