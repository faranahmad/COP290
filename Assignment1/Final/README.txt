Screen Saver Application Version 1.0 25/01/2015

Available for Linux only. Coming soon for Windows!

-----------------------
Running Under Linux OS
-----------------------

The application supports three kinds of modes as described below. 

###### 3D screensaver ###### 

--To run 3D screensaver application, type the following command in the terminal.
$ make Run3D num_thread = n 
where 'n' is the input given by the user and represents total number of balls to be displayed on the screen.
--To print the 'cout' statements used in the program for debugging purposes, type the following command in the terminal.
$ make Run3DPrintDebug num_thread = n 
--To use GDB debugger, type the following command in the terminal.
$ make Run3DGDBDebug num_thread = n

###### 2D screensaver with same number of balls and threads ######

--To run 2D screensaver application, type the following command in the terminal. 
$ make Run2D num_thread = n 
Or
$ make execute NUM_THREAD = n 
where 'n' is the input given by the user and represents total number of balls to be displayed on the screen.
--To print the 'cout' statements used in the program for debugging purposes, type the following command in the terminal.
$ make Run2DPrintDebug num_thread = n
--To use GDB debugger, type the following command in the terminal.
$ make Run2DGDBDebug num_thread = n
or 
$ make DEBUG

###### 2D screensaver with different number of balls and threads ######

--To run the application, type the following command in the terminal.
$ make Run2DMN m = "number of threads" n = "number of balls per thread" 
where "number of threads" and "number of balls per thread" are natural numbers to be given as input.
--To print the 'cout' statements in used in the program for debugging purposes, type the following command in the terminal.
$ make Run2DMNPrintDebug m = "number of threads" n = "number of balls per thread"
--To use GDB debugger, type the following command in the terminal.
$ make Run2DMNGDBDebug m = "number of threads" n = "number of balls per thread"

###### Documentation for all the code ######
--To generate documentation for all the codes in the program.
$make Documentation
Now in the folder 3 pdf files will be generated for the documentation of the 3D, 2D and 2DMN case


--------------------
General Usage Notes
--------------------

###### Using 2D screensaver ######

There are six buttons at the bottom of the screen that can be used to customize the screensaver according to the user.
 
--Pause button-- The button is used to pause the movement of all the balls on the screen.
--Play button-- The button is used to continue the movement of all the balls in the direction and with the velocity as they were before the screen was paused.
--(+) button-- The button is used to increase the total number of balls on the screen. The new balls would start from random positions having random velocities.
--(-) button-- The button can only be used when the screen is in the paused state. Once in the paused state, the ball to be deleted is selected by the user, using the left mouse click. The (-) button can be used to remove the selected ball.
--(Up Arrow button)-- The button can only be used in the paused state of the application. It is used to increase the velocity of the selected ball. The ball whose velocity is to be increased is selected by using the left mouse click. The up arrow button can be used to increase its velocity as many fold as we want. NOTE: The velocity has an upper limit.
--(Down Arrow button)--The button can only be used in the paused state of the machine. It is used to decrease the velocity of the selected ball. The ball whose velocity is to be decreased is selected by using the left mouse click. The down arrow button can be used to decrease its velocity as many fold as we want. 
--ESC key-- The button can be used to exit the application.

###### Using 3D screensaver ######

The following keyboard keys and mouse buttons can be used to customize the screensaver acccording to the user. 

--Arrow keys-- The buttons can be used to rotate the screensaver along the X and Y axes, so as to get the view from various angles.
--Mouse Left Click-- Clicking left button of the mouse and dragging it in any direction would rotate the screensaver in that particular direction. It can be used as an alternative way to view the box from different angles.
--Mouse scroll button--Scroll button can be used to zoom in and zoom out the screen.
--(+) key-- The button is used to increase the number of balls on the screen.
--space bar-- The button is used to pause the movement of all the balls on the screen.
--ESC key-- The button is used to quit the application.

=========================================================================================================================================
