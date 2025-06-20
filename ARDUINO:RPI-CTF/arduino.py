import serial
import time

# ASCII decode helper
def ascii_decode(ascii_list):
    return ''.join([chr(c) for c in ascii_list])

# Attempt to connect to Arduino
try:
    ser = serial.Serial('/dev/cu.usbmodem14401', 9600)  # Update to match your Arduino port
    time.sleep(2)  # Wait for Arduino to reset
except serial.SerialException as e:
    print(f"⚠️ Serial connection error: {e}")
    exit()

# Send message to Arduino
def send_serial_signal(signal):
    ser.write((signal + "\n").encode())

# Core flag checking logic
def handle_flag(flag_number, ascii_flag):
    correct_value = ascii_decode(ascii_flag)

    while True:
        user_input = input(f"Enter Flag {flag_number} (or type 'quit' to exit): ").strip().lower()

        if user_input == 'quit':
            print("Exiting...")
            exit()

        if user_input == correct_value:
            send_serial_signal("pass")
            print("✅ Correct!")
            break
        else:
            send_serial_signal("fail")
            print("❌ Wrong! Try again or type 'quit'.")

# All flags encoded in ASCII
flag_encodings = {
    1: [102, 108, 97, 103, 123, 122, 51, 114, 48, 98, 49, 116, 51, 125],  
    2: [102, 108, 97, 103, 123, 112, 105, 50, 97, 114, 100, 117, 125],  
    3: [102, 108, 97, 103, 123, 99, 115, 115, 95, 102, 108, 97, 103, 51, 125],  
    4: [102, 108, 97, 103, 123, 114, 105, 99, 107, 95, 114, 111, 108, 108, 125],  
    5: [102, 108, 97, 103, 123, 116, 64, 115, 107, 53, 95, 99, 111, 109, 112, 108, 51, 116, 51, 125]  
}

# Individual flag functions
def flag1():
    handle_flag(1, flag_encodings[1])

def flag2():
    handle_flag(2, flag_encodings[2])

def flag3():
    handle_flag(3, flag_encodings[3])

    while True:
        print("\n➡️  Go to the website and enter the code you received.")
        user_code = input("Enter the code from the website: ").strip().lower()

        if user_code == "let5roll":
            send_serial_signal("four")
            print("🎵 I like this song - Listen and look for the clue")
            break
        else:
            send_serial_signal("fail")
            print("❌ Incorrect code. Try again.")

def flag4():
    handle_flag(4, flag_encodings[4])

def flag5():
    handle_flag(5, flag_encodings[5])

# Main logic
try:
    flag1()
    flag2()
    flag3()
    flag4()
    flag5()
    print("🎉 All flags completed!")
    send_serial_signal("celebrate")

finally:
    ser.close()
    print("Thanks for playing!")
