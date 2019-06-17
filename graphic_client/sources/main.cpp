#include "SDL.hpp"
#include "protocols.h"
#include <vector>

int main(void)
{
    srv_tile_content_t tmpTile0;
    tmpTile0.x = 0;
    tmpTile0.y = 0;
    tmpTile0.q0 = 0;
    tmpTile0.q1 = 0;
    tmpTile0.q2 = 0;
    tmpTile0.q3 = 0;
    tmpTile0.q4 = 0;
    tmpTile0.q5 = 0;
    tmpTile0.q6 = 0;

    srv_tile_content_t tmpTile1;
    tmpTile1.x = 0;
    tmpTile1.y = 1;
    tmpTile1.q0 = 0;
    tmpTile1.q1 = 0;
    tmpTile1.q2 = 0;
    tmpTile1.q3 = 0;
    tmpTile1.q4 = 0;
    tmpTile1.q5 = 0;
    tmpTile1.q6 = 0;

    srv_tile_content_t tmpTile2;
    tmpTile2.x = 0;
    tmpTile2.y = 2;
    tmpTile2.q0 = 0;
    tmpTile2.q1 = 0;
    tmpTile2.q2 = 0;
    tmpTile2.q3 = 0;
    tmpTile2.q4 = 0;
    tmpTile2.q5 = 0;
    tmpTile2.q6 = 0;

    srv_tile_content_t tmpTile3;
    tmpTile3.x = 0;
    tmpTile3.y = 3;
    tmpTile3.q0 = 0;
    tmpTile3.q1 = 0;
    tmpTile3.q2 = 0;
    tmpTile3.q3 = 0;
    tmpTile3.q4 = 0;
    tmpTile3.q5 = 0;
    tmpTile3.q6 = 0;

    srv_tile_content_t tmpTile4;
    tmpTile4.x = 0;
    tmpTile4.y = 4;
    tmpTile4.q0 = 0;
    tmpTile4.q1 = 0;
    tmpTile4.q2 = 0;
    tmpTile4.q3 = 0;
    tmpTile4.q4 = 0;
    tmpTile4.q5 = 0;
    tmpTile4.q6 = 0;

    srv_map_size_t tmpSize;
    tmpSize.x = 5;
    tmpSize.y = 5;

    WindowCreator tmp("Test", 800, 600);

    Tile testCase0(&tmpTile0, &tmpSize, "resources/Item_700.png", tmp.getRender());
    Tile testCase1(&tmpTile1, &tmpSize, "resources/Item_700.png", tmp.getRender());
    Tile testCase2(&tmpTile2, &tmpSize, "resources/Item_700.png", tmp.getRender());
    Tile testCase3(&tmpTile3, &tmpSize, "resources/Item_700.png", tmp.getRender());
    Tile testCase4(&tmpTile4, &tmpSize, "resources/Item_700.png", tmp.getRender());

    std::vector<Tile *> tmpC;
    tmpC.push_back(&testCase0);
    tmpC.push_back(&testCase1);
    tmpC.push_back(&testCase2);
    tmpC.push_back(&testCase3);
    tmpC.push_back(&testCase4);

    tmp.updateTileList(tmpC);
    tmp.life();
    return (0);
}
