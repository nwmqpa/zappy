# TODO

This is the `TODO` file tracking what we have to do and what we have done.

## Server :computer:

### Board (AKA Trantor) :earth_africa:

The board is the where the players will be living during the game.
* Composed of tiles :black_square_button:
* Is flat :mount_fuji:
* Spherical :black_circle:

### Ressources :diamond_shape_with_a_dot_inside:

There must be generated randomly by the server. :abcd:

* linemate
* deraumere
* sibur
* mendiane
* phiras
* thystame

### Trantorians (Entities) :smile:

#### Are
* Feeding :meat_on_bone:
* Searching ressources :eyeglasses:
* Collecting ressources :open_hands:

#### Properties
* Bodiless :cloud:
* Pacifist :triangular_flag_on_post:
* Field of view :eyes:
* Cannot now his direction :arrow_heading_up:
* Need food to survive :gun:
* 1 food = 126 unit of time :clock10:

### Elevation :+1:
The elevation is a ritual augmenting capacity of a Trantorians.
It needs 2 things:
- Stones
- Players with the same level

There is a table describing how it works.

![](https://i.imgur.com/iS4QiX1.png)

### Vision :sunglasses:
The players have a field of view.
When the player have to look it shoold send `look` command to the server.
Then the server will send a response in like that.
```
[player , object-on-tile 1 , ..., object-on-tile N , etc...]
```

It can have multiple object on the same tile. So just separte them by a `space`.

### Sound
Players can hear sounds.
They can know from where it come from and the content of the sonore message.

:::warning
The message should take the shortest path.
:::
