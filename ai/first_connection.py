"""First connection to server, get basic info (team name, map width/height)."""


import socket
import sys
import ai.get_args


class client_info:
    """Structure to stock options."""

    def __init__(self, team_name: str, team_nb: str, x: str, y: str):
        """Init variables."""
        self.team_name = team_name
        self.team_nb = team_nb
        self.map_width = x
        self.map_height = y

    def __str__(self) -> str:
        """Get arguments infos."""
        ret = ("client_info -> <team_name: {} team_nb: {} " +
               "map_width: {} map_heigth: {}>").format(
            self.team_name,
            self.team_nb,
            self.map_width,
            self.map_height
        )
        return ret

    def __repr__(self) -> str:
        """Return string."""
        return str(self)


def connect_socket(opt: ai.get_args.Options) -> socket.socket:
    """First connection to the server."""
    HOST = opt.machine
    PORT = opt.port
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((HOST, PORT))
    except ValueError:
        print('Connection to server failed')
        sys.exit(84)
    return (server_socket)


def get_client_nb_and_world_size(
        server_socket: socket.socket, opt: ai.get_args.Options) -> client_info:
    """First interaction with server -> Welcome then team_nb and world_size."""
    new_data = server_socket.recv(1024)
    TEAM_NAME = opt.name
    try:
        server_socket.send((TEAM_NAME + "\n").encode())
    except ValueError:
        print("Can't send data to server")
        sys.exit(84)
    new_data = server_socket.recv(1024)
    parsed_line = new_data.split()
    team_nb = parsed_line[0].decode()
    world_x = parsed_line[1].decode()
    world_y = parsed_line[2].decode()
    return (client_info(opt.name, team_nb, world_x, world_y))
