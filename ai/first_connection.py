"""First connection to server, get basic info (team name, map width/height)"""

import socket
import sys
from clear_received_message import clean_received_message

class team_info:
    """Structure to stock options"""
    def __init__(self, team_name, team_nb, x, y):
        self.team_name = team_name
        self.team_nb = team_nb
        self.map_width = x
        self.map_height = y

    def __str__(self):
        ret = "team_info -> <team_name: {} team_nb: {} map_width: {} map_heigth: {}>".format(
            self.team_name,
            self.team_nb,
            self.map_width,
            self.map_height
        )
        return ret

    def __repr__(self):
        return str(self)

def connect_socket(opt):
    """First connection to the server"""
    HOST = opt.machine
    PORT = opt.port
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((HOST, PORT))
        # print('Connection to server success')
    except:
        print('Connection to server failed')
        sys.exit(84)
    return (server_socket)

def get_client_nb_and_world_size(server_socket, opt):
    """First interaction with server -> Welcome then team_nb and world_size"""
    new_data = server_socket.recv(1024)     # Recv Welcome message
    # print('Received ->', repr(new_data))    # print welcome message
    TEAM_NAME = opt.name
    try:
        server_socket.send((TEAM_NAME + "\n").encode())
    except:
        print("Can't send data to server")
        sys.exit(84)
    new_data = server_socket.recv(1024)     # recv -> b'client_nb\nworld_x wolrd_y\n'
    # print('Received ->', repr(new_data))    # print client_nb and world_size
    new_data = str (repr(new_data))
    new_data = clean_received_message(new_data)
    parsed_line = new_data.split()
    team_nb = parsed_line[0]
    world_x = parsed_line[1]
    world_y = parsed_line[2]
    info = team_info(opt.name, team_nb, world_x, world_y)
    return (info)