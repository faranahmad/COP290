import Tkinter
import tkMessageBox

top = Tkinter.Tk()

def helloCallBack():
	print "Clicked on button"
	exit()
	# tkMessageBox.showinfo( "Hello Python", "Hello World")

B = Tkinter.Button(top, text ="Exit", command = helloCallBack)


B.pack()
top.mainloop()
