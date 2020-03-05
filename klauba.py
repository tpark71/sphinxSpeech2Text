import snowboydecoder
from record import start_recording
import os
import sys
import signal

interrupted = False
kill_script = False
def detected():
    global detector
    # detector.terminate() # THIS LINE CAN CREATE HANGS ON CERTAIN MACHINES (COMMENT OUT IF THE SCRIPT HANGS)
    print("Starting recording")
    data, open_wave = start_recording()
    open_wave.close()
    print("Recording complete")
    global interrupted
    interrupted = True # signal to the detector to stop after first detection

def signal_handler(signal, frame):
    global interrupted
    interrupted = True
    
    global kill_script
    kill_script = True


def interrupt_callback():
    global interrupted
    return interrupted


# capture SIGINT signal, e.g., Ctrl+C
signal.signal(signal.SIGINT, signal_handler)

detector = snowboydecoder.HotwordDetector("./models/Klauba.pmdl", sensitivity=0.5)
print('Listening for Klauba...')

# main loop
detector.start(detected_callback=detected,
               interrupt_check=interrupt_callback,
               sleep_time=0.03)

if os.path.exists("./inputs/raw_recording.wav"):
    print ("I heard: ")
    os.system("pocketsphinx_continuous -infile ./inputs/raw_recording.wav \
            -dict dicts/8050.dic \
            -lm dicts/8050.lm \
            -logfn /dev/null")
else: print ('There is no input to detect')


if kill_script:
    sys.exit(1) # the user hit cntrl-c
else:
    sys.exit(0) # the user did not hit cntrl-c
