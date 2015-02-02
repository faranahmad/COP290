from UserVerification.py import User

class UserDataBase:
	#contains a list of all the users

	def LoadFromFile(self,filedir):
		f=open(filedir)
		contents=f.read()

	def StoreToFile(self,filedir):

	def GetNthUser(self,n):
		if (n>0 and n<len(self.UserLists)):
			return UserLists

	def GetNumberOfUsers(self):
		return len(self.UserLists)

	def CheckUserExists(self,user):
		lo,hi=0,len(self.UserLists)
		verified=False
		while (lo<hi) and not(verified):
			mid=(lo+hi)/2
			midstr=self.GetNthUser(mid)
			if(midstr.GetUserName()==user.GetUserName()):
				verified=True
				return True
			elif(midstr.GetUserName()<user.GetUserName()):
				lo=mid+1
			else:
				hi=mid
		return verified

	def AddUser(self,newuser):
		if not(self.CheckUserExists(newuser)):
			self.UserLists.append(newuser)
			self.UserLists.sort(key=lambda x: x.GetUserName())

	def VerifyUser(self,userinput):
		lo,hi=0,len(self.UserLists)
		verified,completed=False,False
		while (lo<hi) and not(verified) and not(completed) :
			mid=(lo+hi)/2
			midstr=self.GetNthUser(mid)
			if(midstr.GetUserName()==userinput.GetUserName()):
				completed=True
				verified= (userinput.GetUserPassword()==midstr.GetUserPassword())
				return verified
			elif(midstr.GetUserName()<userinput.GetUserName()):
				lo=mid+1
			else:
				hi=mid
		return Completed

	def __init__(self):
		self.UserLists=[]

	def __str__(self):
		return str(self.UserLists)
