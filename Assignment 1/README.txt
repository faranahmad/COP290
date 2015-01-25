Screen Saver Application Version 1.0 25/01/2015

Available for LINUX users only.

Running Under Linux OS
-----------------------
The application support three kinds of modes as followed 

#3D screensaver# 
--To run 3D screen saver application type the following command in terminal 
$ make RUN3D num_thread=n 
where n is the input given by the user and the represents the total number of balls to be displayed on the screen.
--To print the cout statements in used in the program type the following command in the terminal
$ make RUN3DPrintDebug num_thread=n
--To use GDB debugger type
$ make RUN3DGDBDebug num_thread=n

#2D screen saver with same number of balls and threads#
--To run 2D application type the following command in terminal 
$ make RUN2D num_thread=n 
where n is the input given by the user and the represents the total number of balls to be displayed on the screen.
--To print the cout statements in used in the program type the following command in the terminal
$ make RUN2DPrintDebug num_thread=n
--To use GDB debugger type
$ make RUN2DGDBDebug num_thread=n