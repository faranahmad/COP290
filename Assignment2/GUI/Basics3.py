# from Tkinter import *
# 
# top = Tk()
# bottom = Tk()
# L1 = Label(top, text="User Name")
# L1.pack( side = LEFT)
# L2 = Label(top, text="User Name")
# L2.pack( side = LEFT)
# E1 = Entry(bottom, bd =5)
# 
# E1.pack(side = RIGHT)
# 
# top.mainloop()

# from Tkinter import *
# master = Tk()
# def show_entry_fields():
   # print("Username: %s\npassword: %s" % (e1.get(), e2.get()))
   # master.quit
   # exit()
   # e1.delete(0,END)
   # e2.delete(0,END)
# 
# 
# Label(master, text="Username").grid(row=0, pady = 10, padx = 10)
# Label(master, text="Password").grid(row=1, pady = 10, padx = 10)
# 
# e1 = Entry(master)
# e2 = Entry(master, show = '*')
# e1.insert(10,"Miller")
# e2.insert(10,"Jill")
# 
# e1.grid(row=0, column=1, pady = 10)
# e2.grid(row=1, column=1, pady = 10)
# 
# Button(master, text='Quit', command=master.quit).grid(row=3, column=1, pady = 10, padx = 10)
# Button(master, text='Login', command=show_entry_fields).grid(row=3, column=0, pady = 10, padx = 10 )
# 
# mainloop( )
from Tkinter import *

root = Tk()
scrollbar = Scrollbar(root)
x = Scrollbar(root)
scrollbar.pack( side = RIGHT, fill=Y )
x.grid(column = 0)
mylist = Listbox(root, yscrollcommand = scrollbar.set )
for line in range(100):
   mylist.insert(END, "This is line number " + str(line))

mylist.pack( side = LEFT, fill = BOTH )
scrollbar.config( command = mylist.yview )

mainloop()


