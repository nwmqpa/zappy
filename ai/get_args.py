"""Get options and return it in structure."""

import sys
import getopt
import ai.verif

class Options:
    """Structure to stock options."""

    def __init__(self, port, name, machine):
        """Init port, name, machine."""
        self.port = port
        self.name = name
        self.machine = machine

    def __str__(self):
        """Put them in an str."""
        ret = "Options -> <port: {} name: {} machine: {}>".format(
            self.port,
            self.name,
            self.machine
        )
        return ret

    def __repr__(self):
        """Return str."""
        return str(self)


def fill_my_args(optlist):
    """Put options in structur and return it."""
    occ = 0
    for x in optlist:
        for y in optlist:
            if x[0] == y[0]:
                occ = occ + 1
            if occ > 1:
                verif.display_help()
                sys.exit(0)
        occ = 0
    for x in optlist:
        if (x[0] == "-p"):
            _port = x[1]
        if (x[0] == "-n"):
            _name = x[1]
        if (x[0] == "-h"):
            _machine = x[1]
    args = Options(_port, _name, _machine)
    return (args)


def get_arguments():
    """Parse options and fill structur with them, then return it."""
    args = sys.argv
    args.pop(0)
    try:
        optlist, args = getopt.getopt(args, 'p:n:h:')
    except getopt.GetoptError:
        verif.display_help()
        sys.exit(0)
    args = fill_my_args(optlist)
    return (args)
