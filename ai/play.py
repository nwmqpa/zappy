"""All functions to play."""

from ai.parse_inventory import parse_inventory
from ai.parse_inventory import Inventory
from ai.parse_vision import parse_vision
from ai.parse_vision import Vision
from ai.parse_vision import verif_look_response
from ai.queue import Queue
from threading import Thread
import socket
import sys
from typing import List
from typing import Dict
from typing import Optional
import time


class Player:
    """All player action to live."""

    def __init__(self, server_socket: socket.socket) -> None:
        """Set basic infos."""
        self.server_socket = server_socket
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

    def send_msg(self, message: str) -> None:
        """Send message to server."""
        self.server_socket.send((message + "\n").encode())

    def recv_msg(self) -> str:
        """Return received message from server."""
        received = self.server_socket.recv(1024).decode()
        if (received == "dead\n"):
            print("Player is dead.")
            exit(0)
        while (received[len(received) - 1] != '\n'):
            received = received + self.server_socket.recv(1024).decode()
        return (received)

    def is_a_response_to_comand(self, line: str) -> bool:
        """Return True if line is a response to a command."""
        """Return False if line is a broadcast or eject."""
        splitted_line = line.split(" ")
        if (splitted_line[0] == "message" or splitted_line == "eject:"):
            return (False)
        return (True)

    def check_ok_ko_response(self, response: str) -> bool:
        """Verify if response is `ok` or `ko` else command don't count."""
        if (response == "ok\n" or response == "ko\n"):
            return (True)
        return (False)

    def read_oldest_response(self) -> str:
        """Return oldest response to command from server."""
        while (self.my_queue.size() == 0):
            i = 0
            # print("Waiting...")
        # print(self.my_queue.printQueue())
        response = self.my_queue.first_in()
        if (self.is_a_response_to_comand(response) is True):
            self.my_queue.dequeue()
            return (response)
        else:
            splitted_line = response.split(" ")
            if (splitted_line[0] == "message"):
                print("It's a broadcast message.")
                return ("")
        return ("")

    def other_player_nb_on_tile(self) -> int:
        """Return nb of other player on same tile."""
        self.send_msg("Look")
        response = self.recv_msg()
        if (verif_look_response(response) is False):
            print("Bad response from server.\n", response)
            print("Pass.")
            return (-1)
        response = response.replace("[ ", "")
        response = response.replace(" ]", "")
        array = str(response).split(",")
        player_nb = -1
        tile_1 = array[0]
        splited = tile_1.split(" ")
        for i in splited:
            if (str(i) == "player"):
                player_nb = player_nb + 1
        return (player_nb)

    def check_inventory(self) -> Inventory:
        """Check what's is in my Inventory."""
        print("Check Inventory.")
        self.send_msg("Inventory")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (response == ""):
            return
        inventory = parse_inventory(response)
        # if (inventory is None):
        #     print("Bad response from server.\n", response)
        #     print("Pass.")
        #     return None
        return (inventory)

    def look_around(self) -> List[Vision]:
        """Look command to see what's in front of me."""
        self.send_msg("Look")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        environment = parse_vision(response)
        return (environment)

    def take_object(self, object: str) -> int:
        """Take an object and add it to my inventory."""
        self.send_msg("Take " + object)
        print("Take " + object)
        # self.units_of_time = int(self.units_of_time) - 7
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (self.check_ok_ko_response(response) is False):
            return (-1)
        if (response != "ok\n"):
            print("Response is ->", response)
            print("Can't take the object :(.")
            return(-1)
        else:
            print("Response is ->", response)
            print("Add `" + object + "` to inventory.")
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
            return (1)
        return (2)

    def set_object(self, object: str) -> int:
        """Set an object on tile and remove it from inventory."""
        self.send_msg("Set " + object)
        print("Set " + object)
        # self.units_of_time = int(self.units_of_time) - 7
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (self.check_ok_ko_response(response) is False):
            return (-1)
        if (response != "ok\n"):
            print("Response is ->", response)
            print("Can't set the object :(.")
            return(-1)
        else:
            print("Response is ->", response)
            print("Remove `" + object + "` from inventory.")
            if object == "food":
                self.inventory.food = str(int(self.inventory.food) - 1)
            elif object == "linemate":
                self.inventory.linemate = str(int(self.inventory.linemate) - 1)
            elif object == "deraumere":
                self.inventory.deraumere = str(int(self.inventory.deraumere)+1)
            elif object == "sibur":
                self.inventory.sibur = str(int(self.inventory.sibur) - 1)
            elif object == "mendiane":
                self.inventory.mendiane = str(int(self.inventory.mendiane) - 1)
            elif object == "phiras":
                self.inventory.phiras = str(int(self.inventory.phiras) - 1)
            elif object == "thystame":
                self.inventory.thystame = str(int(self.inventory.thystame) - 1)
            return (1)
        return (2)

    def should_take(self, stone: str) -> bool:
        """Return True if we have to pickup this stone, else return False."""
        if (stone == "food" and int(self.inventory.food) < 10):
            return (True)
        elif (stone == "linemate" and int(self.inventory.linemate) < 9):
            return (True)
        elif (stone == "deraumere" and int(self.inventory.deraumere) < 8):
            return (True)
        elif (stone == "sibur" and int(self.inventory.sibur) < 10):
            return (True)
        elif (stone == "mendiane" and int(self.inventory.mendiane) < 5):
            return (True)
        elif (stone == "phiras" and int(self.inventory.phiras) < 6):
            return (True)
        elif (stone == "thystame" and int(self.inventory.thystame) < 1):
            return (True)
        return(False)

    def choose_stone_to_take(self, actual_level: int) -> int:
        """Determine what stone to pick up."""
        level = actual_level - 1
        environment = self.look_around()
        print("Look around for stone:")
        print(*environment, sep="\n")
        print("\nDetermine what stone to pick up.")
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
              self.should_take("thystame") is True):
            return(self.take_object("thystame"))
        print("\nCan't take any stone.\n")
        if (int(actual_tile.food) > 0):
            print("So will take a food.\n")
            return(self.take_object("food"))
        return(0)

    def move_forward(self) -> int:
        """Move player `Forward`."""
        print("\nPlayer move `Forward`.")
        self.send_msg("Forward")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (self.check_ok_ko_response(response) is False):
            print("Bad response from server.\n", response)
            print("Pass.")
            return (-1)
        print("Response for player move ->", response)
        return (0)

    def turn_right(self) -> int:
        """Make player turn `Right`."""
        print("\nPlayer move `Right`.")
        self.send_msg("Right")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (self.check_ok_ko_response(response) is False):
            print("Bad response from server.\n", response)
            print("Pass.")
            return (-1)
        print("Response for player move ->", response)
        return (0)

    def turn_left(self) -> int:
        """Make player turn `Left`."""
        print("\nPlayer move `Left`.")
        self.send_msg("Left")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        if (self.check_ok_ko_response(response) is False):
            print("Bad response from server.\n", response)
            print("Pass.")
            return (-1)
        print("Response for player move ->", response)
        return (0)

    def where_to_move(self) -> None:  # not finished
        """Determine if player move forward, turn right or left."""
        print("In where to move.")
        if (self.move_forward() == -1):
            return
        # self.turn_left()
        # self.turn_right()
        # raise NotImplementedError

    def verif_stones(self, inventory: Inventory,
                     stones_combinations: Dict[str, int]) -> bool:
        """Verif if my inventory allow me to elevate."""
        if (int(inventory.linemate) >= stones_combinations["linemate"] and
            int(inventory.deraumere) >= stones_combinations["deraumere"] and
            int(inventory.sibur) >= stones_combinations["sibur"] and
            int(inventory.mendiane) >= stones_combinations["mendiane"] and
            int(inventory.phiras) >= stones_combinations["phiras"] and
                int(inventory.thystame) >= stones_combinations["thystame"]):
            return (True)
        return (False)

    def put_stones(self, stones_combinations: Dict[str, int]) -> None:
        """Put on tile stones to elevate."""
        stones_names = ["linemate",
                        "deraumere",
                        "sibur",
                        "mendiane",
                        "phiras",
                        "thystame"]
        stone_nb = 0
        for stone in stones_names:
            # print("__________---------------------------> ", stone)
            stone_nb = stones_combinations[stone]
            while (stone_nb > 0):
                self.set_object(stone)
                stone_nb = stone_nb - 1

    def incantation(self) -> bool:
        """Start incantation to elevate level."""
        print("\nPlayer ask for Incantation.")
        self.send_msg("Incantationt")
        # response = self.recv_msg()
        response = self.read_oldest_response()
        print("Response for `Incantation`:", response)
        if (response == "ko\n"):
            print("Level still -> ", self.actual_level)
            return (False)
        else:
            return (True)

    def elevate(self) -> None:
        """Verify if player can elevate."""
        print("\nIn elevate function.\n")
        level = self.actual_level
        if (level == 1 and self.verif_stones(self.inventory,
            self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 0):
            print("Actual level == 1")
            print("Player elevate to level 2 !")
            # print(self.look_around())
            # self.put_stones(self.stones_combinations[level - 1])
            # print("+++++++++++++++++++++++++++++++++=")
            # print(self.look_around())
            if (self.incantation() is True):
                self.actual_level = 2
        elif (level == 2 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 1):
            print("Actual level == 2")
            print("Player elevate to level 3 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 3
        elif (level == 3 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 1):
            print("Actual level == 3")
            print("Player elevate to level 4 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 4
        elif (level == 4 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 3):
            print("Actual level == 4")
            print("Player elevate to level 5 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 5
        elif (level == 5 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 3):
            print("Actual level == 5")
            print("Player elevate to level 6 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 6
        elif (level == 6 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 5):
            print("Actual level == 6")
            print("Player elevate to level 7 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 7
        elif (level == 7 and self.verif_stones(self.inventory,
              self.stones_combinations[level - 1]) is True and
                self.other_player_nb_on_tile() == 5):
            print("Actual level == 7")
            print("Player elevate to level 8 !")
            # self.put_stones(self.stones_combinations[level - 1])
            if (self.incantation() is True):
                self.actual_level = 8

    def listener(self) -> None:
        """Threaded function to always listen to server."""
        print("----------- In broadcast listener -----------")
        while (self.listening is True):
            self.server_socket.settimeout(0.5)
            try:
                received = self.server_socket.recv(1024).decode()
            except:
                break
            if (received == "dead\n"):
                print("Player is dead.")
                exit(0)
            while (received[len(received) - 1] != '\n'):
                received = received + self.server_socket.recv(1024).decode()

            print("FINAL of thread = ", received)
            self.response_from_thread = received
            self.my_queue.enqueue(received)
            received = ""

    def farm_mode(self) -> None:
        """Mode where player live normaly."""

        print("\n+++\nFarm mode loop !\n")
        self.inventory = self.check_inventory()
        print(self.inventory)
        print("")
        # print("MY STUFF -> ", self.inventory)

        self.choose_stone_to_take(self.actual_level)
        # self.elevate()
        self.where_to_move()

    def join_mode(self) -> None:
        """Mode where player join other to elevate."""
        print("\n+++\nJoin player loop !\n")

    def start_response_listener(self) -> None:
        """Start thread to listen to server responses."""
        self.my_queue = Queue()
        listening_thread = Thread(target=self.listener, args=())
        listening_thread.start()

    def life_loop(self) -> None:
        """Main loop of player attitude."""
        print("Begin of loop.\n")
        i = 0
        while (i < 50):
            if (self.FARM_MODE is True):
                self.farm_mode()
            elif (self.join_mode is True):
                self.join_mode()
            i = i + 1
        self.listening = False
        print("--------------")

    def begin_player_life(self) -> None:
        """Initiate player modes and start life."""
        self.FARM_MODE = True
        self.JOIN_MODE = False
        self.listening = True
        self.start_response_listener()
        self.life_loop()

        # self.my_queue.enqueue("1")
        # self.my_queue.enqueue("2")
        # self.my_queue.enqueue("3")
        # print(self.my_queue.first_in())
        # self.my_queue.enqueue("4")
        # self.my_queue.dequeue()
        # print(self.my_queue.printQueue())
        # print(self.my_queue.queue[self.my_queue.size() - 1])
        # self.my_queue.dequeue()
        # print(self.my_queue.printQueue())
        # print(self.my_queue.queue[self.my_queue.size() - 1])

        # print("1--> ".join(self.result))
        # print("2--> ", self.result)
