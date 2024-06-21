

# Door Locker Security System
This project implements a door locker security system using two ATmega32 microcontrollers. The system allows a user to unlock a door using a password, with an interface for entering and confirming the password, and various functionalities to handle password entry and verification.

## Introduction
The Door Locker Security System uses two ATmega32 microcontrollers to manage user interaction and system control. The system features a human-machine interface (HMI) with an LCD and keypad, and a control unit (Control_ECU) that handles password verification, door control, and alarm activation.


## Hardware Requirements

• ATmega32 Microcontroller

• 4x4 Keypad

• EEPROM

• Buzzer

• DC Moto

• 16x2 LCD Display

• Breadboard or PCB for assembly

• Connecting wires

• Power supply (5V for ATmega32 and sensor)

## System Architecture
### HMI_ECU (Human Machine Interface)
- Microcontroller: ATmega32
- Components: 16x2 LCD, 4x4 Keypad
- Function: Interacts with the user for password entry and displays messages.

### Control_ECU
- Microcontroller: ATmega32
- Components: EEPROM, Buzzer, DC Motor
- Function: Handles password processing, door control, and alarm activation.

## System Sequence

### Step 1 - Create a System Password
1. The LCD displays "Please Enter Password".
2. The user enters a 5-digit password, with each digit displayed as *.
3. The user presses the enter button (designated key on the keypad).
4. The LCD prompts "Please re-enter the same Pass".
5. The user re-enters the password for confirmation.
6. The HMI_ECU sends both passwords to the Control_ECU via UART.
7. If the passwords match, the Control_ECU saves the password to EEPROM and proceeds to Step 2.
8. If the passwords do not match, the system repeats Step 1.

### Step 2 - Main Options
- The LCD displays the main system options.
        
       +:open door
       -:change pass

### Step 3 - Open Door
1. The LCD displays "Please Enter Password".
2. The user enters the password and presses the enter button.
3. The HMI_ECU sends the password to the Control_ECU.
4. The Control_ECU compares the entered password with the one stored in EEPROM.
5.  If the passwords match:
    * The motor rotates clockwise for 15 seconds, and the LCD displays "Door is Unlocking".
     * The motor holds for 3 seconds.
      * The motor rotates counter-clockwise for 15 seconds, and the LCD displays "Door is Locking".

### Step 4 - Change Password
1. The LCD displays "Please Enter Password".
2. The user enters the password and presses the enter button.
3. The HMI_ECU sends the password to the Control_ECU.
4. The Control_ECU compares the entered password with the one stored in EEPROM.
5. If the passwords match, repeat Step 1 to create a new password.

###Step 5 - Incorrect Password Handling

1. If the entered password is incorrect in Step 3 or Step 4, prompt the user to re-enter the password.
2. Allow up to three attempts to enter the correct password.
3. If the password is correct, proceed with the respective steps for opening the door or changing the password.
4. If the password is incorrect after three attempts:
     - Activate the buzzer for 1 minute.
     - Display an error message on the LCD for 1 minute.
      - Lock the system for 1 minute, during which no inputs are accepted.
      - Return to the main options menu after 1 minute.

## Schematic
![Schematic](https://github.com/Malak-Nabil/Door-Locker-Security-System/assets/112269807/b95f66fd-fabe-4cc5-826b-359183a2cf61)

## Setting Up the Simulation

• Open Proteus: Launch the Proteus design software.

• Load Project: Open the final project.pdsprj file from the repository.

• Run Simulation: Start the simulation to see the Door Locker Security System in action.

• Interact:  Use the virtual keypad to enter passwords and observe the LCD display updates and motor operation.
