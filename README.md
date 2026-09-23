# Gantry Crane Motion Control

A gantry crane prototype that moves a trolley along two axes (longitudinal and transversal) and controls a hoist to raise/lower a payload — simulating industrial overhead crane automation.

## How it works
- Ultrasonic sensors measure the trolley's position on both axes in real time
- The operator selects a target position via push-button controls, shown on an LCD menu
- DC motors move the trolley to the selected coordinates, closing the loop against live sensor feedback
- A separate motor controls the hoist to raise or lower the hook

## Hardware
- Arduino Mega
- 2x ultrasonic sensors (position feedback)
- 4x DC motors (trolley movement + hoist)
- 16x2 LCD display
- 3x push buttons for menu navigation
