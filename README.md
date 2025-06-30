# Call Center Comunication System Design: Master Microcontroller
- PIC16F628A microcontrollers that manage multiple slave microphones are programmed in MPLAP IDE.
- In this system: We have 4 radio channels, each channel can be used by at most one of the slave microphones at the same time, and the master directs the microphone used to the relevant radio channel.
- According to these restrictions, decision algorithm developed in C language for master microcontrollers by defining state variables for each channel and using the USART system of the PIC16F628A microcontroller.
