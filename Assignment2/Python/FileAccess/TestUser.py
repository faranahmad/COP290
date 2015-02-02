from UserVerification import User

def InitialisationTest():
	user1=User("Kartikeya")
	print user1.GetUserPassword()==""
	print user1.GetUserName()=="Kartikeya"


def RunAllTests():
	InitialisationTest()

RunAllTests()