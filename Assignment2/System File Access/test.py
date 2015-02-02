import os

databaseDir='/home/skipper/Desktop/Dropbox/COP290/Assignment\ 2/Database/'
usersDir='/home/skipper/Desktop/Dropbox/COP290/Assignment\ 2/Users/'

def sync(username):
    try:
        if not os.path.exists(databaseDir):
            os.makedirs(databaseDir)
        if not os.path.exists(usersDir+username+'/'):
            raise NameError("User not found")
        for elem in os.listdir(usersDir+'/'+username):
            if elem not in os.listdir(databaseDir):
                os.system('cd ' + databaseDir + ';cp ' + elem + ' ' + databaseDir)
    except(NameError):
        print ('Error found')
if __name__== '__main__':
    sync('Faran')
