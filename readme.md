# Windshield Wiper Control System Project

This project aims to develop a comprehensive windshield wiper control system for automobiles, expanding beyond conventional functionality to include four distinct modes: High-Speed (HI), Low-Speed (LO), Intermittent (INT), and Off (OFF). The system incorporates features such as smooth ramping of the wiper angle in high-speed and low-speed modes, with no discernible hesitation at either end of the motion. Additionally, it introduces an intermittent mode that mimics low-speed operation but includes customizable pause intervals at the 0-degree position. Through user-selectable delay times, ranging from 3 to 8 seconds, the system provides adaptability to varying weather conditions. Moreover, an integrated user display communicates the selected wiper mode, enhancing driver awareness and control. The overarching goal is to deliver a reliable and user-friendly windshield wiper control system that enhances visibility and safety for vehicle occupants.

## Contributors

- Spencer Aldrich
- Samantha Scanlon
- Zuhair AlMassri


## Wiper Modes and Characteristics

- **High-Speed (HI)**: Wipers operate at maximum speed, with the wiper angle ramping up and down from 0 to a maximum of 67 degrees at 40 rpm.
- **Low-Speed (LO)**: Similar to high-speed mode but operates at 30 rpm.
- **Intermittent (INT)**: Functions like low-speed mode but with a pause at the 0-degree position for a driver-selectable delay time (3, 6, or 8 seconds).
- **Off (OFF)**: Wipers remain stationary at 0 degrees.

## System Components

The vehicle is equipped with several devices:
- Driver seat occupancy sensor (detects occupied seat)
- Ignition push button (starts and stops the engine)
- Blue indicator LED (indicates engine running)
- Wiper mode selector (chooses HI, LO, INT, or OFF)
- Intermittent delay time selector (chooses delay time)
- Windshield wiper motor (controls wiper movement)
- User display (shows mode settings)

## Desired Behaviors

### Ignition Subsystem
- Start the engine when the driver's seat is occupied and the ignition button is pushed.
- Keep the engine running even if the driver exits the vehicle.
- Stop the engine when the ignition button is pushed and released while the engine is running.

### Windshield Wiper Subsystem
- If the engine is running and a wiper mode is selected, run the wipers accordingly with typical parameters.
- Display the selected mode, including delay time for INT mode.
- If the wiper mode is set to OFF or the engine is turned off:
  - Complete the current wiper cycle if in motion.
  - If hesitating in INT mode, remain stationary.

## Implementation Details

- Utilize buttons for the driver seat sensor and ignition switch.
- Use potentiometers for the wiper mode selector and intermittent delay time selector.
- Choose between a continuous or position servo motor to simulate the windshield wiper motor.
- A 2x20 LCD display will serve as the user display.

---

### Ignition Subsystem

| Specification                                                                                                     | Test Result | Comment                                                                       |
|-------------------------------------------------------------------------------------------------------------------|-------------|-------------------------------------------------------------------------------|
| Start the engine (i.e., light the blue LED) while the driver’s seat is occupied and when the ignition button is pushed and then released. | Pass        | Works 100% of the time, but the button must be held for at least half a second and released before the engine turns on. |
| Keep the engine running even if the driver should exit the vehicle.                                              | Pass        |                                                                               |
| When the engine is running, stop the engine when the ignition button is pushed and then released.                | Pass        |                                                                               |

### Windshield Wiper Subsystem

| Specification                                                                                        | Test Result | Comment                                                         |
|------------------------------------------------------------------------------------------------------|-------------|-----------------------------------------------------------------|
| User is able to select between HI, LOW, INT, or OFF.                                                | Pass        |                                                                 |
| If INT mode is selected, the wiper (servo) rotates based on the delay setting.                      | Pass        |                                                                 |
| Display shows the status of both the wiper mode and the delay setting.                               | Pass        |                                                                 |
| If wiper mode selector is turned off or engine is turned off, wipers freeze in their current position | Pass        | Challenge 2 - Implemented in place of completing the current cycle and returning to zero. |
| When ignition is turned back on, the servo returns to the starting position of 0 degrees.             |     Pass    |                                                                 |
