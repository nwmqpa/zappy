"""Parse the Look command -> return Array of Object with present things."""


class vision:
    """Structure to stock Inventory"""
    def __init__(self, tile_nb, food, linemate, deraumere, siur, mendiane, phiras, thystame):
        """__init__."""
        self.tile_nb = tile_nb
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.siur = siur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self):
        """__str__."""
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
        """__repr__."""
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
    food = linemate = deraumere = siur = mendiane = phiras = thystame = 0
    for x in array:
        splited = x.split(" ")
        # print("splited -> ", splited)
        food = linemate = deraumere = siur = mendiane = phiras = thystame = 0
        for i in splited:
            if (str(i) == "food"):
                food = food + 1
            elif (str(i) == "linemate"):
                linemate = linemate + 1
            elif (str(i) == "deraumere"):
                deraumere = deraumere + 1
            elif (str(i) == "siur"):
                siur = siur + 1
            elif (str(i) == "mendiane"):
                mendiane = mendiane + 1
            elif (str(i) == "phiras"):
                phiras = phiras + 1
            elif (str(i) == "thystame"):
                thystame = thystame + 1
        tile = tile + 1
        environnement.append(vision(tile, food, linemate, deraumere, siur, mendiane, phiras, thystame))
    for x in environnement: # print current vision
        print(x)