
"""Main function to execute AI."""

from ai.verif import basic_verif
from ai.verif import verif_args_values
from ai.get_args import get_arguments
from ai.first_connection import connect_socket
from ai.first_connection import get_client_nb_and_world_size
from ai.clear_received_message import clean_received_message
from ai.parse_inventory import parse_inventory
import socket
import sys


def look_around(server_socket: socket.socket) -> None:
    """Look command to see what's in front of me."""
    print('Send     ->', "Look")    # send message
    server_socket.send(("Look" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    parse_vision(new_data)
    print("Recv =====>", new_data, "\n")


def check_inventory(server_socket: socket.socket):
    """Check what's is in my Inventory."""
    print('Send     ->', "Inventory")    # send message
    server_socket.send(("Inventory" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    inventory = parse_inventory(new_data_str)
    print("Inventory -> ", inventory)
    # print("Recv =====>", new_data, "\n")
    print("")


def send_message(server_socket: socket.socket, message: str):
    """Broadcast message to all players."""
    print('Send     ->', "Broadcast text")    # send message
    server_socket.send(("Broadcast " + message + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")


def get_connection_nb(server_socket: socket.socket) -> int:
    """Return nb of connected players."""
    print('Send     ->', "Connect_nbr")     # sned message
    server_socket.send(("Connect_nbr" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")
    return (int(new_data))


def all_commands(server_socket):
    """All_command to send to server."""
    print("IN TEST\n")

    look_around(server_socket)
    check_inventory(server_socket)
    send_message(server_socket, "LOLILOL")
    get_connection_nb(server_socket)

    # new_data = server_socket.recv(1024)     # Recv message
    # # print('Received ->', repr(new_data))    # print message
    # new_data = clean_received_message(repr(new_data))
    # print("Recv =====>", new_data, "\n")


def main() -> None:
    """Main."""
    basic_verif()
    opt = get_arguments()
    verif_args_values(opt)

    # print(repr(opt))
    server_socket = connect_socket(opt)
    client_info = get_client_nb_and_world_size(server_socket, opt)
    print("Client info -> ", repr(client_info) + "\n")

    # while (1):
    test(server_socket)
    all_commands(server_socket)
