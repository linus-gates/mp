import machine

def set(num):
    pin = machine.Pin(num, machine.Pin.OUT)
    pin.value(1)

def reset(num):
    pin = machine.Pin(num, machine.Pin.OUT)
    pin.value(0)

print("Welcome to debugging example : ")
print("debug.set(23) to set")
print("debug.reset(23) to reset")