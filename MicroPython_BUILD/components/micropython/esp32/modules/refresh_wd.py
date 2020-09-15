import machine
import time
import _thread

GPIO_NUM = 5

def set(num):
    pin = machine.Pin(num, machine.Pin.OUT)
    pin.value(1)

def reset(num):
    pin = machine.Pin(num, machine.Pin.OUT)
    pin.value(0)

def rfs_wd():

    print("refreshing watchdog")

    while (True):
        set(GPIO_NUM)
        time.sleep(3)
        reset(GPIO_NUM)
        time.sleep(3)

def start_thread(func, args = (), stackSize=4096):
    _ = _thread.stack_size(stackSize)
    _thread.start_new_thread("refresh wd", func, args)

start_thread(rfs_wd)
#rfs_wd()