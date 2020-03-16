
// PROJECT CREATED BY: SAHIL YADAV

This project uses:

* 170 PL9823 leds
* 12V to 5V buck converter (atleast 6amps)
* Analog microphone module with amplifier and auto gain
* 12V power supply
* brass wire/tin wire of suitable thickness for structure and electrical conductivity
* general tools and intermediate electronics/programming knowledge

Files included:

* Code file: canton_tower_code.ino
* Cad file : Assembly.stp
* leds template .dxf

//---------------------------

// TIP/GUIDE:

//---------------------------

Each Led has 4 pins:
DATA IN
DATA OUT
5V
GND

The first led's DATA IN pin is hooked up to digital pin on arduino and the DATA OUT of the same led is connected to the next
led's data in and so on..

choice of wiring is upto you.
*	*In my case all the vertical rails are 5V and are on the outside of each LED level/ring and all the ground rail are on the inside of each ring/level.
 	 and all the ground of each ring are connected with power/structural rails inside the tower.
 
*	*Every single level has one DATA IN and one DATA OUT. The bottom level data in is connected to the microcontroller unit whereas the data out is connected
 	 to the data in of the next level and so on..

