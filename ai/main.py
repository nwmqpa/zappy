"""Main function to execute AI."""


from ai.verif import basic_verif
from ai.verif import verif_args_values
from ai.get_args import get_arguments
from ai.first_connection import connect_socket
from ai.first_connection import get_client_nb_and_world_size
from ai.parse_inventory import parse_inventory
from ai.parse_vision import parse_vision
import socket
import sys


def look_around(server_socket: socket.socket) -> None:
    """Look command to see what's in front of me."""
    print('Send     ->', "Look")
    server_socket.send(("Look" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    environment = parse_vision(new_data)
    print(*environment, sep="\n")
    print("")


def check_inventory(server_socket: socket.socket) -> None:
    """Check what's is in my Inventory."""
    print('Send     ->', "Inventory")
    server_socket.send(("Inventory" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    inventory = parse_inventory(new_data)
    print("Inventory -> ", inventory)
    print("")


def send_message(server_socket: socket.socket, message: str) -> None:
    """Broadcast message to all players."""
    print('Send     ->', "Broadcast text")
    server_socket.send(("Broadcast " + message + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    print("Recv =====>", new_data, "\n")


def get_connection_nb(server_socket: socket.socket) -> int:
    """Return nb of connected players."""
    print('Send     ->', "Connect_nbr")     # send message
    server_socket.send(("Connect_nbr" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    print("Recv =====>", new_data, "\n")
    return (int(new_data))


def move_forward(server_socket: socket.socket) -> None:
    """Move plyer Forward."""
    print('Send     ->', "Forward")     # send message
    server_socket.send(("Forward" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    print("Recv =====>", new_data, "\n")


def turn_right(server_socket: socket.socket) -> None:
    """Make player turn Right."""
    print('Send     ->', "Right")     # send message
    server_socket.send(("Right" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    print("Recv =====>", new_data, "\n")


def turn_left(server_socket: socket.socket) -> None:
    """Make player turn Left."""
    print('Send     ->', "Left")     # send message
    server_socket.send(("Left" + "\n").encode())
    new_data = server_socket.recv(1024).decode()
    print("Recv =====>", new_data, "\n")


def all_commands(server_socket: socket.socket) -> None:
    """All_command to send to server."""
    look_around(server_socket)
    check_inventory(server_socket)
    send_message(server_socket, "LOLILOL")
    get_connection_nb(server_socket)
    move_forward(server_socket)
    turn_right(server_socket)
    turn_left(server_socket)

    # new_data = server_socket.recv(1024).decode()
    # # print('Received ->', repr(new_data))
    # print("Recv =====>", new_data, "\n")


def main() -> None:
    """Main."""
    basic_verif()
    opt = get_arguments()
    verif_args_values(opt)
    server_socket = connect_socket(opt)
    client_info = get_client_nb_and_world_size(server_socket, opt)
    print("Client info -> ", repr(client_info) + "\n")
    all_commands(server_socket)
