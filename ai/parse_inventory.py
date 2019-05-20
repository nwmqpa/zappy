class inventory:
    """Structure to stock Inventory"""
    def __init__(self, food, linemate, deraumere, siur, mendiane, phiras, thystame):
        self.food = food
        self.linemate = linemate
        self.deraumere = deraumere
        self.siur = siur
        self.mendiane = mendiane
        self.phiras = phiras
        self.thystame = thystame

    def __str__(self):
        ret = "inventory -> food: {} linemate: {} deraumere: {} siur: {} mendiane: {} phiras: {} thystame: {}>".format(
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

def parse_inventory(line):
    """Parse Inventory answer sent by server and return an inventory object"""
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
    curr_inventory = inventory(curr_food, curr_linemate, curr_deraumere, curr_siur, curr_mendiane, curr_phiras, curr_thystame)
    return (curr_inventory)