#include "UserBaseTests.h"

bool RunAllUserBaseTests()
{
	UserBaseInitialisationTests();
	AddingUserTests();
	EncryptionTests();
}

bool UserBaseInitialisationTests()
{
	Test t("Testing initialisation of user base");
	UserBase u;	
	t.VerifyTrue(u.GetNumberOfUsers()==0,"number of users should be 0");
}

bool AddingUserTests()
{
	Test t("Testing additions of users in base");
	UserBase u;
	u.InsertUser(User("name", "password"));
	t.VerifyTrue(u.GetNumberOfUsers()==1,"Number of users should be 1");
}

bool EncryptionTests()
{
	Test t("Testing encryption of user base");
	t.VerifyTrue(EncryptDecrypt(EncryptDecrypt("hello"))=="hello", " encrypt decrypt should return same result");
}