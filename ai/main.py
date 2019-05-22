
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

class vision:
    """Structure to stock Inventory"""
    def __init__(self, tile_nb, food, linemate, deraumere, siur, mendiane, phiras, thystame):
        self.tile_nb = tile_nb
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.siur = siur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self):
        ret = "Vision -> tile_nb: {} food: {} linemate: {} deraumere: {} siur: {} mendiane: {} phiras: {} thystame: {}>".format(
            self.tile_nb,
            self.food,
            self.linemate,
            self.deraumere,
            self.siur,
            self.mendiane,
            self.phiras,
            self.thystame
        )
        return ret

    def __repr__(self):
        return str(self)

def parse_vision(line):
    """Look arround in return array with present object"""
    print("In parse Vison\n")
    environnement = []
    line = line.replace("[ ", "")
    line = line.replace(" ]", "")
    # print("line -> ", line)
    array = str(line).split(",")
    # print("sss -> ", array)

    tile = 0
    food = 0
    linemate = 0
    deraumere = 0
    siur = 0
    mendiane = 0
    phiras = 0
    thystame = 0
    for x in array:
        splited = x.split(" ")
        # print("splited -> ", splited)
        food = 0
        linemate = 0
        deraumere = 0
        siur = 0
        mendiane = 0
        phiras = 0
        thystame = 0
        for i in splited:
            if (str(i) == "food"):
                food = food + 1
            if (str(i) == "linemate"):
                linemate = linemate + 1
            if (str(i) == "deraumere"):
                deraumere = deraumere + 1
            if (str(i) == "siur"):
                siur = siur + 1
            if (str(i) == "mendiane"):
                mendiane = mendiane + 1
            if (str(i) == "phiras"):
                phiras = phiras + 1
            if (str(i) == "thystame"):
                thystame = thystame + 1
        tile = tile + 1
        environnement.append(vision(tile, food, linemate, deraumere, siur, mendiane, phiras, thystame))
    for x in environnement:
        print(x)

def test(server_socket):
    print("In test\n")

    print('Send     ->', "Look")    # send message
    server_socket.send(("Look" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    parse_vision(new_data)
    print("Recv =====>", new_data, "\n")

    print('Send     ->', "Inventory")    # send message
    server_socket.send(("Inventory" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    inventory = parse_inventory(new_data_str)
    print("Inventory -> ", inventory)
    # print("Recv =====>", new_data, "\n")
    print("")

    print('Send     ->', "Broadcast text")    # send message
    server_socket.send(("Broadcast Text Message Wesh" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")

    print('Send     ->', "Connect_nbr")    # sned message
    server_socket.send(("Connect_nbr" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data_str = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")

    # new_data = server_socket.recv(1024)     # Recv message
    # # print('Received ->', repr(new_data))    # print message
    # new_data = clean_received_message(repr(new_data))
    # print("Recv =====>", new_data, "\n")


def main() -> None:
    """Main."""
    basic_verif()
    opt = get_arguments()
    verif_args_values(opt)

    print(repr(opt))
    server_socket = connect_socket(opt)
    client_info = get_client_nb_and_world_size(server_socket, opt)
    print("Client info -> ", repr(client_info) + "\n")

    test(server_socket)
