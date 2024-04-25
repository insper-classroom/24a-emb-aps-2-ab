import serial
import uinput

ser = serial.Serial('/dev/rfcomm0', 9600)

# Create new mouse device
device = uinput.Device([
    uinput.BTN_LEFT,
    uinput.BTN_RIGHT,
    uinput.REL_X,
    uinput.REL_Y,
])


def parse_data(data):
    axis = data[0]  # 0 for X, 1 for Y
    value = int.from_bytes(data[1:3], byteorder='little', signed=True)
    print(f"Received data: {data}")
    print(f"axis: {axis}, value: {value}")
    return axis, value


# def move_mouse(axis, value):
#     if axis == 0:    # X-axis
#         device.emit(uinput.REL_X, value)
#     elif axis == 1:  # Y-axis
#         device.emit(uinput.REL_Y, value)


try:
    # sync package
    while True:
        print('Waiting for sync package...')
        while True:
            data = ser.read(1)
            print(data)
            if data == b'\xff':
                break

        # Read 4 bytes from UART
        data = ser.read(1)
        pyautogui.press(data)
        # axis, value = parse_data(data)
        # move_mouse(axis, value)

except KeyboardInterrupt:
    print("Program terminated by user")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    ser.close()

# import serial
# import pyautogui

# ser = serial.Serial('/dev/ttyACM1', 115200)

# def parse_data(data):
#     if data == b'a':
#         key = 'a'
#     elif data == b's':
#         key = 's'
#     elif data == b'd':
#         key = 'd'
#     elif data == b'w':
#         key = 'w'
#     else:
#         key = None
#         print(f"Received unknown data: {data}")
#     return key
# try:
#     while True:
#         print('Waiting for data...')
#         data = ser.read(1)
#         key = parse_data(data)
#         if key:
#             pyautogui.press(key)

# except KeyboardInterrupt:
#     print("Program terminated by user")
# except Exception as e:
#     print(f"An error occurred: {e}")
# finally:
#     ser.close()
