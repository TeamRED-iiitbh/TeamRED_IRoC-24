import serial
import serial.tools.list_ports
from pynput import keyboard

# Prompt the user to select a serial port
port_selection = 'COM10'

# Open the serial connection
try:
    ser = serial.Serial(port_selection, 115200)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

print("Serial connection established.")

# Action state mapping
action_states = {
    keyboard.Key.up: 'F',  # Move forward
    keyboard.Key.left: 'L',  # Turn left
    keyboard.Key.right: 'R',  # Turn right
    keyboard.Key.down: 'B',  # Move backward
    'q': 'S',  # Stop motors
    keyboard.Key.shift_l: 'N',
}

current_action = None

def on_press(key):
    global current_action
    if key in action_states:
        current_action = action_states[key]
    
    elif key == keyboard.Key.esc:
        # Stop listener and exit program
        listener.stop()
        return False

def on_release(key):
    global current_action
    if key == keyboard.Key.shift:
        current_action = None

# Start the keyboard listener
listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

while True:
    if current_action:
        command = current_action.encode()
        ser.write(command)
        print(f"Sent command: {current_action}")

# Close the serial connection when the script is stopped
ser.close()