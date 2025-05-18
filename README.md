# Circuit Schematics
Refer to the temp-sensor-report.pdf (Appendices 5: Figures 6 & 7) for circuit schematics.

# Introduction
For this project, the customer desired an electronic thermometer. Within this report, our decision process will be outlined and explained. This includes project requirements, project restraints, background research, and our decision matrix. It then goes on to explain how we built and tested the product till it reached its final form. Afterwards, there is a discussion on failures and future improvements.

# Project Requirements and Constraints
Specific requirements
* Minimum thermometer range:  -10° to 150°F
* Minimum thermometer accuracy:  ±2C°
* Minimum 4 LEDs used within the circuit
* Visual output in Celsius and Fahrenheit
* Switch must be integrated into Arduino software

General requirements
* Must be able to measure general room temperature
* Must be relatively small
* Must have some visual display of the temperature

Constraints
* Must use one of the following temperature sensors:
  - TMP36
  - LM34
  - LM334
  - AD 592
  - TMP37
  - LM61
* Must use a microcontroller
* Must utilize a switch in some manner

# Background Research
When researching the available transducers we were allowed to use, we made a set of qualities that we would be looking for. This included, but was not limited to qualities such as accuracy at room temperature, maximum inaccuracy, voltage output, and maximum temperature range. Most transducers had accuracy within our requirements, and most had the correct temperature range. However we noticed that both the AD592 and LM334 output a current instead of a voltage, and we deemed them to be harder to work with.

# Building and Testing
Initially, we first wanted to get any output from the TMP36. At first, we almost destroyed the transducer by confusing the GND and Vin pins. Once figuring those out, we wrote very basic code to get the analog reading pin working with the sensor. After getting a reading, we did some research on how the Arduino reads the sensor. Using the information, we were able to reverse the reading process and get actual voltage readings from the sensor. Then, using the data sheet provided for the sensor, we could find the temperature in Celsius based on the voltage reading. After getting the temperature reading, we decided on how we wanted to take care of inaccurate extraneous results. Our decision was to take the results multiple times a second, and average them, displaying the average approximately every second. When implementing that, it succeeded the first time, and we tried varying numbers until we had an accurate and stable reading. We then attempted to implement the LCD into the circuit. When implementing it, we ran into an issue with the breadboard we chose being faulty. We then had to replace the breadboard and move all the components to a new one. After some trial and error, along with more research on specifically implementing it with an arduino, we got the LCD to display the text of the temperature. Next, we decided to get the button working to change the display on the LCD. We went through multiple versions of the code until we got one that was efficient and worked. We ended up creating two separate outputs, and toggled which one was displayed based on if the button was pressed upon refresh of the display. The button was integrated into the circuit with very few issues. Then, we had to decide what information the LEDs would display. Initially, we discussed if they should be simple tasks such as turning one on when the device is working. After realizing we had multiple colors of LEDs, we decided to use three of them for a temperature range. The red would turn on when it is “hot”, the blue for “cold”, and the green for “room temperature”. The final LED ended up being used for every refresh of the display, it would flash. Initially, due to the small size of the breadboard, we had a hard time making the LEDs work with resistors properly. After realizing the LEDs didn’t burn out without resistors, we solved a lot of our spacing issues with the breadboard. Overall, the project went through many iterations, mainly with the code being redone and cleaned up multiple times, and the circuit being rebuilt a few times.

# Demo Results:
The project ended up with minor issues with potential cross-wiring, or lack of resistors, and a mistake in one of the lines of code pertaining to the refresh led. Some potential improvements that could be made to the device could be more organized cable management as well as potentially adding a resistor to the LEDs to constrain the brightness as well as stop any leaking of voltage to affect the other LEDs in the vicinity. A simple fix that we could immediately implement would be to fix our code for the refresh LED as we have an invalid parameter for it. We would have also liked to clean up the code for the LEDs as it was a lot of if and else statements. 

