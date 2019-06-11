"""All functions to play."""

# One unit of food allows them to live for 126 units of time.
# units_of_time = check_inventory().food * 126

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

    def send_msg(self, message: str) -> None:
        """Send message to server."""
        self.server_socket.send((message + "\n").encode())

    def recv_msg(self) -> str:
        """Return received message from server."""
        return (self.server_socket.recv(1024).decode())

    def check_inventory(self) -> Inventory:
        """Check what's is in my Inventory."""
        # print('Send     ->', "Inventory")
        self.send_msg("Inventory")
        new_data = self.recv_msg()
        inventory = parse_inventory(new_data)
        # print("Inventory -> ->  ", inventory)
        return (inventory)

    def look_around(self) -> List[Vision]:
        """Look command to see what's in front of me."""
        print('Send     ->', "Look")
        self.send_msg("Look")
        new_data = self.recv_msg()
        environment = parse_vision(new_data)
        print(*environment, sep="\n")
        print("")
        return (environment)

    def life_loop(self) -> None:
        """Player life."""
        print("Begin of loop.\n")
        i = 0
        while (i < 1):
            self.inventory = self.check_inventory()
            print(self.inventory)
            environment = self.look_around()
            i = i + 1
