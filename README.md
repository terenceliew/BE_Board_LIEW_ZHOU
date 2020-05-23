# Security Door Equipped With Burglar Alert System
This is a project done in conjunction with 4th year INSA Toulouse module on C++.  This project is a simulation of a small model of security door equipped with burglar alert system. It is done with a simulation of an arduino board integrated with various simulated devices (sensors and actuators). More fonctions can be added to enhance the application.

## Installation 
1.  First of all, retrieve this git project to your local repository.
1.  Direct yourself to `src` folder from terminal.
1.  Create the following files in `src` folder and insert the corresponding default value to each file. Caution !!! Make sure to key in these values in one line in each file (Do not press `Enter` after keying in these values) !!! :
    + `force.txt` : `10`
    + `savedfp.txt` : `1111`
    + `loadfp.txt` : `2222`
    + `savedrfid.txt` : `3333`
    + `loadrfid.txt` : `4444`
    
1.  Execute the following code to compile base on your operating system:
```bash
../compile_linux.sh
```
```bash
../compile_mac.sh
```
1.  Execute the following code to start the programme.
```bash
./arduino
```

## Terminal Presentation
After starting the programme, you will notice several lines starting from `Serial : `. These lines display the states and values of sensors and actuators used in the project. You will also notice the the two lines starting with `---screen : `. The sentences that comes after them shows the display of the screens installed. One of the screen is installed outside of the door whereas the other is inside. Indications are shown with the words `((Inside))` and `((Outside))`.

## How it works?
### Indoor Button
#### Function
This button is used to simulate an unlock door button situated inside a room. The door is open when the angle is `180` and close when it's `0`.
#### Execution
+ While running the programme, create a `.txt` file with the name `indoor.txt` in the `src` folder to open the door. 
+ Delete the file created to close the door. 

### Outdoor Button
#### Function
This button is used to simulate a doorbell situated outside a room. The buzzer will ring at 480 MHz when the doorbell is pressed, and at 0 MHz when the button is released.
#### Execution
+ While running the programme, create a `.txt` file with the name `outdoor.txt` in the `src` folder to ring the doorbell. 
+ Delete the file created to mute the doorbell.

### Fingerprint System
#### Function
This system is capable of detecting fingerprint and unlock the door if fingerprint matches the saved fingerprint. This system also allows to set a new fingerprint. The detected fingerprint ID is loaded to `loadfp.txt` file, whereas the saved fingerprint ID is stored in `savedfp.txt`. For this version, only one fingerprint ID can be stored.
#### Execution
+ By default the values of the fingerprint IDs does not match. 
+ To open the door, change the ID in `loadfp.txt` so that it's similar to the one in `savedfp.txt`.
+ To close the door, key in a different value of fingerprint ID in `loadfp.txt` than the one in `savedfp.txt`.
+ To set a new fingerprint ID, key in the new fingerprint ID in `loadfp.txt` and create a new file in `src` folder named `setFp.txt`. The value in `loadfp.txt` will be copied automatically to `savedfp.txt`. Note that the door will not open when the `setFp.txt` file is still present in the `src` folder. Delete it to open the door.

### RFID System
#### Function
This system is capable of detecting an RFID card and unlock the door if the RFID frequency corresponds to the saved frequency. The detected frequency of RFID is loaded in `loadrfid.txt`, whereas the saved frequency is stored in `savedrfid.txt`.
#### Execution
+ By default the frequency detected does not matched the one saved.
+ To open the door, changed the frequency ID in `loadrfid.txt` so that it's similar to the one in `savedrfid.txt`.
+ To close the door, key in a different value of fingerprint ID in `loadrfid.txt` than the one in `savedrfid.txt`.

### Burglar Alert System
#### Function
This system is capable of detecting the force exerted on the door through a force sensor. A signal will be sent to a buzzer (the same as doorbell but with higher frequency) that alarms the owner when the force exerted to the door exceeds a defined limit (by default 88). The detected force is stored in the file `force.txt`.
#### Execution
+ Increase the value to more than 88 in order to ring the buzzer at highest frequency (500 MHz). Note that the door is prevented from being opened when the alert is ongoing. 
+ Decrease the value back to less than 88 in order to mute the buzzer and return to normal function of the door.

## What do you see?
Screens situated at the inside and outside of the door gives instructions to user.
+ During normal state when the door is closed and there is no interactions with the sensor, the     following messages are displayed on the screens: 
```
((Inside)) Please press the indoor button !
((Outside)) Please scan your fingerprint ! The doorbell is on your left !
```
+ When door is open by using any type of identification, the following messages are displayed on the screens :
```
((Inside)) Door is open !
((Outside)) Door is open !
```
+ When someone press the doorbell from outside : 
```
((Inside)) Someone is at the door !
((Outside)) Please scan your fingerprint ! The doorbell is on your left !
```
+ When the burglar alert is triggered :
```
((Inside)) Burglar Alert!!! Calling Police...
((Outside)) Don't force the door, the police is coming !!!
```

## Exception and Limits for Sensors
+ Fingerprint Sensor : 0-55555 
+ RFID Sensor : 0-44444
+ Force Sensor : 0-100

## Branches
+ `master` :  The newest stable version.
+ `dev1` : For development purpose
+ `dev2` : For development purpose
+ `old_version` : Initial version before integrating this application

## Authors and Acknowledgment
This project is done by Terence Chun Heng LIEW and Zheng ZHOU under the guidance of Raphaël Deau.



