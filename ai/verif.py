import os
import sys

def display_help():
    print("USAGE: ./zappy_ai -p port -n name -h machine\n"
    "   port    is the port number\n"
    "   name    is the name of the team\n"
    "   machine is the name of the machine; localhost by default")

def basic_verif():
    if (len(sys.argv) == 2 and (sys.argv[1] == "-h" or sys.argv[1] == "--help")):
        display_help()
        sys.exit(0)
    elif (len(sys.argv) != 7):
        display_help()
        sys.exit(84)

def verif_args_values(my_opt):
    try:
        my_opt.port = int(my_opt.port)
    except:
        print("Port should be an integer")
        display_help()
        sys.exit(0)
    if (my_opt.port > 65535 or my_opt.port <= 1023):
        print("Invalid port")
        display_help()
        sys.exit(0)
    HOST_UP  = True if os.system("ping -c 1 " + my_opt.machine + " > /dev/null") is 0 else False
    if (HOST_UP == False):
        print("Invalid host")
        sys.exit(0)