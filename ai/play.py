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
        self.inventory = Inventory
        self.units_of_time = 0
        self.actual_level = 1
        self.stones_combinations = [{
                                        "linemate": 1,
                                        "deraumere": 0,
                                        "sibur": 0,
                                        "mendiane": 0,
                                        "phiras": 0,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 1,
                                        "deraumere": 1,
                                        "sibur": 1,
                                        "mendiane": 0,
                                        "phiras": 0,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 2,
                                        "deraumere": 0,
                                        "sibur": 1,
                                        "mendiane": 0,
                                        "phiras": 2,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 1,
                                        "deraumere": 1,
                                        "sibur": 2,
                                        "mendiane": 0,
                                        "phiras": 1,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 1,
                                        "deraumere": 2,
                                        "sibur": 1,
                                        "mendiane": 3,
                                        "phiras": 0,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 1,
                                        "deraumere": 2,
                                        "sibur": 3,
                                        "mendiane": 0,
                                        "phiras": 1,
                                        "thystame": 0
                                    },
                                    {
                                        "linemate": 2,
                                        "deraumere": 2,
                                        "sibur": 2,
                                        "mendiane": 2,
                                        "phiras": 2,
                                        "thystame": 1
                                    }]
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

    def take_object(self, object: str) -> int:
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
                self.inventory.food = str(int(self.inventory.food) + 1)
            elif object == "linemate":
                self.inventory.linemate = str(int(self.inventory.linemate) + 1)
            elif object == "deraumere":
                self.inventory.deraumere = str(int(self.inventory.deraumere)+1)
            elif object == "sibur":
                self.inventory.sibur = str(int(self.inventory.sibur) + 1)
            elif object == "mendiane":
                self.inventory.mendiane = str(int(self.inventory.mendiane) + 1)
            elif object == "phiras":
                self.inventory.phiras = str(int(self.inventory.phiras) + 1)
            elif object == "thystame":
                self.inventory.thystame = str(int(self.inventory.thystame) + 1)
        return (2)

    def get_stone_nb(self, stone: str) -> int:
        """Return number of this stone in inventory."""
        # print(self.inventory.get_item(stone))
        return(self.inventory.get_item(stone))

    def should_take(self, stone: str) -> bool:
        """Return True if we have to pickup this stone."""
        if (stone == "food" and self.get_stone_nb("food") < 10):
            return (True)
        elif (stone == "linemate" and self.get_stone_nb("linemate") < 9):
            return (True)
        elif (stone == "deraumere" and self.get_stone_nb("deraumere") < 8):
            return (True)
        elif (stone == "sibur" and self.get_stone_nb("sibur") < 10):
            return (True)
        elif (stone == "mendiane" and self.get_stone_nb("mendiane") < 5):
            return (True)
        elif (stone == "phiras" and self.get_stone_nb("phiras") < 6):
            return (True)
        elif (stone == "thystame" and self.get_stone_nb("thystame") < 1):
            return (True)
        return(False)

    def choose_stone_to_take(self, actual_level: int) -> int:
        """Determine what stone to pick up."""
        level = actual_level - 1
        environment = self.look_around()
        print(*environment, sep="\n")
        # for tile_nb in environment: # Move to a better tile
        actual_tile = environment[0]
        if (int(actual_tile.food) > 0 and
           self.should_take("food") is True):
            return(self.take_object("food"))
        elif (int(actual_tile.linemate) > 0 and
              self.should_take("linemate") is True):
            return(self.take_object("linemate"))
        elif (int(actual_tile.deraumere) > 0 and
              self.should_take("deraumere") is True):
            return(self.take_object("deraumere"))
        elif (int(actual_tile.sibur) > 0 and
              self.should_take("sibur") is True):
            return(self.take_object("sibur"))
        elif (int(actual_tile.mendiane) > 0 and
              self.should_take("mendiane") is True):
            return(self.take_object("mendiane"))
        elif (int(actual_tile.phiras) > 0 and
              self.should_take("phiras") is True):
            return(self.take_object("phiras"))
        elif (int(actual_tile.thystame) > 0 and
              self.should_take("tystame") is True):
            return(self.take_object("thystame"))
        return(0)

    def life_loop(self) -> None:
        """Player life."""
        print("Begin of loop.\n")
        i = 0
        while (i < 1):
            self.inventory = self.check_inventory()
            print(self.inventory, "\n")
            self.units_of_time = int(self.inventory.food) * 126
            # environment = self.look_around()
            # print(*environment, sep="\n")
            print("")
            # self.take_object("food")

            print("MY STUFF -> ", self.inventory)

            self.choose_stone_to_take(self.actual_level)
            print(self.inventory)

            i = i + 1
