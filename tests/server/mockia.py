#!/usr/bin/env python3

import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

team_name = "name{}\n".format(sys.argv[3])
print("Conneting on {} {} in team {}.".format(sys.argv[1], sys.argv[2], team_name));
s.connect((sys.argv[1], int(sys.argv[2])))

s.send(team_name.encode())

while True:
    s.send(b"Forward\n")
