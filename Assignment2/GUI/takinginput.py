from Tkinter import *
master = Tk()
def show_entry_fields():
   print("Username: %s\npassword: %s" % (e1.get(), e2.get()))
   master.quit
   exit()
   e1.delete(0,END)
   e2.delete(0,END)


Label(master, text="Username").grid(row=0, pady = 10, padx = 10)
Label(master, text="Password").grid(row=1, pady = 10, padx = 10)

e1 = Entry(master)
e2 = Entry(master, show = '*')
e1.insert(10,"Miller")
e2.insert(10,"Jill")

e1.grid(row=0, column=1, pady = 10)
e2.grid(row=1, column=1, pady = 10)

Button(master, text='Quit', command=master.quit).grid(row=3, column=1, pady = 10, padx = 10)
Button(master, text='Login', command=show_entry_fields).grid(row=3, column=0, pady = 10, padx = 10 )

mainloop( )
