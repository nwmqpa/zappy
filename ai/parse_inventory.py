"""Parse and manage Inventory."""


import sys


class Inventory:
    """Structure to stock Inventory."""

    def __init__(self, food: str, linemate: str,
                 deraumere: str, sibur: str, mendiane: str,
                 phiras: str, thystame: str) -> None:
        """Init stones."""
        # self.content = {}
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.sibur = sibur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def get_item(self, stone: str) -> int:
        """Return number of stone in inventory."""
        if (str(stone) == "food"):
            return(int(self.food))
        elif (str(stone) == "linemate"):
            return(int(self.linemate))
        elif (str(stone) == "deraumere"):
            return(int(self.deraumere))
        elif (str(stone) == "sibur"):
            return(int(self.sibur))
        elif (str(stone) == "mendiane"):
            return(int(self.mendiane))
        elif (str(stone) == "phiras"):
            return(int(self.phiras))
        elif (str(stone) == "thystame"):
            return(int(self.thystame))
        return(-1)

    def __str__(self) -> str:
        """Fill str."""
        ret = (
            "inventory -> food: {} linemate: {} deraumere: {}" +
            " sibur: {} mendiane: {} phiras: {} thystame: {}>"
        ).format(
            self.food,
            self.linemate,
            self.deraumere,
            self.sibur,
            self.mendiane,
            self.phiras,
            self.thystame
        )
        return ret

    def __repr__(self) -> str:
        """Return str."""
        return str(self)


def parse_inventory(line: str) -> Inventory:
    """Parse Inventory answer sent by server and return an inventory object."""
    line = line.replace("[ ", "")
    line = line.replace(" ]", "")
    array = str(line).split(",")
    curr_food = (array[0].split(" "))[1]
    curr_linemate = (array[1].split(" "))[2]
    curr_deraumere = (array[2].split(" "))[2]
    curr_sibur = (array[3].split(" "))[2]
    curr_mendiane = (array[4].split(" "))[2]
    curr_phiras = (array[5].split(" "))[2]
    curr_thystame = ((array[6].split(" "))[2]).replace("\n", "")
    return (Inventory(
        curr_food, curr_linemate, curr_deraumere,
        curr_sibur, curr_mendiane, curr_phiras, curr_thystame))
