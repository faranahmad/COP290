#include <iostream>
#include "UserTests.h"

bool RunAllUserTests()
{
	UserInitialisationTests();
	UserSettingTests();
}

bool UserInitialisationTests()
{
	Test t("Testing the initialisation of user");
	User u;
	t.VerifyTrue(u.GetUserName()=="","initialised value should be empty");
	t.VerifyTrue(u.GetPassword()=="","initialised value should be empty");	
	u=User("kg","soccer");
	t.VerifyTrue(u.GetUserName()=="kg","initialised value should be kg");
	t.VerifyTrue(u.GetPassword()=="soccer","initialised value should be soccer");	
	return t.isPassed();
}

bool UserSettingTests()
{
	Test t("Testing the Settings of paramaeter");
	User u;
	u.SetUserName("faran");
	u.SetPassword("pokemon");
	t.VerifyTrue(u.GetUserName()=="faran","val should be faran");
	t.VerifyTrue(u.GetPassword()=="pokemon","val should be pokemon");
	return t.isPassed();	
}