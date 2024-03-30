#include "MazeWars\include\mazeWars.h++"
#include "BattleZone\include\battleZone.h++"

int main()
{
    MazeWars::MazeWarsGame mazeWarsGame( {900,900}, {10,10} );
    BattleZone::BattleZoneGame battleZoneGame( {1600,900} );
    return 0;
}