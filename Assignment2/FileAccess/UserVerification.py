class User:
	# Properties are username and password
	# Both are strings
	def GetUserName(self):
		return self.UserName

	def GetUserPassword(self):
		return self.Password

	def SetUserName(self,newname):
		self.UserName=newname

	def UpdatePassword(self,newpass):	
		self.Password=newpass

	def GetInfo(self):
		return str(self)

	def __init__(self,name):
		self.UserName=name
		self.Password=""

	def __str__(self):
		return "Name: " +self.UserName +" Password: " + self.Password
