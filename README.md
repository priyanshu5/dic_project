# dic_project
development of fully automatic grass cutter with multilevel machanism.
##  BACKGROUNG
Here the grass cutter is actully working though remote control. Its will be soon shifted to automatic working, after testing of all machanical structure working in field.
In remote control the communication is done through 'NRF module' at the both end and 'arduino mega' at robot side and 'arduino nano' at remote end.
All the diffirent functions carried out by this grass cutter is controll by using relay switchs.
Two 12V, 9A batteries are use to power up the robot.
## Program details

### REMOTE END

The program at remote end basically reads the value of two joystick, and a switch.
The value of joysticks are stored in the structure variables.
And the structure is being passed to the robot end.

### ROBOT END

Here the value passed from the remote is read, and according to it the different functions are being called to perform various operations, such as moving forward, backward, left, right, blade heigh adjustment, etc.
