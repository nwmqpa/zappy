"""Parse and manage Inventory."""


import sys


class Inventory:
    """Structure to stock Inventory."""

    def __init__(self, food: str, linemate: str,
                 deraumere: str, siur: str, mendiane: str,
                 phiras: str, thystame: str) -> None:
        """Init stones."""
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.siur = siur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self) -> str:
        """Fill str."""
        ret = (
            "inventory -> food: {} linemate: {} deraumere: {}" +
            " siur: {} mendiane: {} phiras: {} thystame: {}>"
        ).format(
            self.food,
            self.linemate,
            self.deraumere,
            self.siur,
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
    curr_siur = (array[3].split(" "))[2]
    curr_mendiane = (array[4].split(" "))[2]
    curr_phiras = (array[5].split(" "))[2]
    curr_thystame = (array[6].split(" "))[2]
    return (Inventory(
        curr_food, curr_linemate, curr_deraumere,
        curr_siur, curr_mendiane, curr_phiras, curr_thystame))
