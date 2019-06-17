"""Parse the Look command return Array of Object with present things."""

from typing import List


class Vision:
    """Structure to stock Inventory."""

    def __init__(
        self, tile_nb: int, food: int, linemate: int,
        deraumere: int, sibur: int, mendiane: int, phiras: int, thystame: int
         ) -> None:
        """__init__."""
        self.tile_nb = tile_nb
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.sibur = sibur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self) -> str:
        """__str__."""
        ret = (
            "Vision -> tile_nb: {} food: {} linemate: {} deraumere: {} " +
            "sibur: {} mendiane: {} phiras: {} thystame: {}>"
            ).format(
            self.tile_nb,
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
        """__repr__."""
        return str(self)


def verif_look_response(line: str) -> bool:
    """Verify if response have a good format."""
    splitted_line = line.split(",")
    if (line[0] != '[' or line[len(line) - 2] != ']'):
        return (False)
    return (True)


def parse_vision(line: str) -> List[Vision]:
    """Look arround in return array with present object."""
    environment = []
    line = line.replace("[ ", "")
    line = line.replace(" ]", "")
    array = str(line).split(",")
    tile = 0
    food = linemate = deraumere = sibur = mendiane = phiras = thystame = 0
    for x in array:
        splited = x.split(" ")
        food = linemate = deraumere = sibur = mendiane = phiras = thystame = 0
        for i in splited:
            # print("I -> ", i)
            if (str(i) == "food"):
                food = food + 1
            elif (str(i) == "linemate"):
                linemate = linemate + 1
            elif (str(i) == "deraumere"):
                deraumere = deraumere + 1
            elif (str(i) == "sibur"):
                sibur = sibur + 1
            elif (str(i) == "mendiane"):
                mendiane = mendiane + 1
            elif (str(i) == "phiras"):
                phiras = phiras + 1
            elif (str(i) == "thystame"):
                thystame = thystame + 1
        tile = tile + 1
        environment.append(
            Vision(
                tile, food, linemate, deraumere,
                sibur, mendiane, phiras, thystame))
    return (environment)
