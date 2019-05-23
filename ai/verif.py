"""Verification file."""

import os
import sys


def display_help():
    """Print usage."""
    print("USAGE: ./zappy_ai -p port -n name -h machine\n"
          "   port    is the port number\n"
          "   name    is the name of the team\n"
          "   machine is the name of the machine; localhost by default")


def basic_verif():
    """Verif number of args."""
    if (len(sys.argv) == 2
            and (sys.argv[1] == "-h" or sys.argv[1] == "--help")):
        display_help()
        sys.exit(0)
    elif (len(sys.argv) != 7):
        display_help()
        sys.exit(84)


def verif_args_values(opt):
    """Verif if options correspond to good types."""
    try:
        opt.port = int(opt.port)
    except ValueError:
        display_help()
        raise Exception("Port should be an integer")
    if (opt.port > 65535 or opt.port <= 1023):
        display_help()
        raise Exception("Invalid port")
    HOST_UP = True if os.system(
        "ping -c 1 " + opt.machine + " > /dev/null") is 0 else False
    if (HOST_UP is False):
        raise Exception("Invalid host")
