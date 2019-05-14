import sys
import verif
import getopt

class My_Arguments:
    def __init__(self, port, name, machine):
        self.port = port
        self.name = name
        self.machine = machine

    def __str__(self):
        ret = "My_Arguments -> <port: {} name: {} machine: {}>".format(
            self.port,
            self.name,
            self.machine
        )
        return ret

    def __repr__(self):
        return str(self)

def fill_my_args(optlist):
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
            # print("-p -> ", x[1])
            _port = x[1]
        if (x[0] == "-n"):
            # print("-n -> ", x[1])
            _name = x[1]
        if (x[0] == "-h"):
            # print("-h -> ", x[1])
            _machine = x[1]
    args = My_Arguments(_port, _name, _machine)
    return (args)

def get_arguments():
    args = sys.argv
    args.pop(0)
    try:
        optlist, args = getopt.getopt(args, 'p:n:h:')
    except getopt.GetoptError:
        verif.display_help()
        sys.exit(0)
    args = fill_my_args(optlist)
    return (args)