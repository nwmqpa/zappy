"""All functions to play."""

from ai.parse_inventory import parse_inventory
from ai.parse_inventory import Inventory
from ai.parse_vision import parse_vision
from ai.parse_vision import Vision
import socket
import sys
from typing import List


class Player:
    """All player action to live."""

    def __init__(self, server_socket: socket.socket) -> None:
        """Init basic infos."""
        self.server_socket = server_socket
        self.inventory = None
        self.units_of_time = 0
        # self.my_stuff = {
        #     "food": 1200,
        #     "linemate": 0,
        #     "deraumere": 0,
        #     "sibur": 0,
        #     "mendiane": 0,
        #     "phiras": 0,
        #     "thystame": 0
        # }

    def send_msg(self, message: str) -> None:
        """Send message to server."""
        self.server_socket.send((message + "\n").encode())

    def recv_msg(self) -> str:
        """Return received message from server."""
        return (self.server_socket.recv(1024).decode())

    def check_inventory(self) -> Inventory:
        """Check what's is in my Inventory."""
        self.send_msg("Inventory")
        new_data = self.recv_msg()
        inventory = parse_inventory(new_data)
        return (inventory)

    def look_around(self) -> List[Vision]:
        """Look command to see what's in front of me."""
        self.send_msg("Look")
        new_data = self.recv_msg()
        environment = parse_vision(new_data)
        return (environment)

    def take_object(self, object: str):
        """Take an object and add it to my inventory."""
        self.send_msg("Take " + object)
        print("Take " + object)
        print("Unit of time before taking the object ->", self.units_of_time)
        self.units_of_time = int(self.units_of_time) - 7
        print("Unit of time after taking the object  ->", self.units_of_time)
        response = self.recv_msg()
        if (response != "ok\n"):
            print("Response is ->", response)
            print("Can't take the object :(.")
            return(-1)
        else:
            print("Response is ->", response)
            print("Add " + object + " to inventory.")
            if object == "food":
                self.inventory.food = int(self.inventory.food) + 1
            elif object == "linemate":
                self.inventory.linemate = int(self.inventory.linemate) + 1
            elif object == "deraumere":
                self.inventory.deraumere = int(self.inventory.deraumere) + 1
            elif object == "sibur":
                self.inventory.sibur = int(self.inventory.sibur) + 1
            elif object == "mendiane":
                self.inventory.mendiane = int(self.inventory.mendiane) + 1
            elif object == "phiras":
                self.inventory.phiras = int(self.inventory.phiras) + 1
            elif object == "thystame":
                self.inventory.thystame = int(self.inventory.thystame) + 1

    def life_loop(self) -> None:
        """Player life."""
        print("Begin of loop.\n")
        i = 0
        while (i < 1):
            self.inventory = self.check_inventory()
            print(self.inventory, "\n")
            self.units_of_time = int(self.inventory.food) * 126
            environment = self.look_around()
            print(*environment, sep="\n")
            print("")

            self.take_object("food")

            i = i + 1
