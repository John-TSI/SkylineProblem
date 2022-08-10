#include"../inc/solution.hpp"

// note: each vector<int> B represents a building: B[0] is left x coord, B[1] is right x coord, B[2] is y coord (height)
std::vector<std::vector<int>> Solution::getSkyline(std::vector<std::vector<int>>& buildings)
{
    std::vector<std::vector<int>> skyline{{buildings[0][0], buildings[0][2]}};  // always at least this first coordinate
    // if only one building, insert the terminating ground-level coord and return
    if(buildings.size()==1){ skyline.push_back( {buildings[0][1], 0} ); return skyline; } 

    int len = buildings.size();
    for(int i{0}; i<len-1; ++i)  // iterate through buildings, implementing a pairwise comparison
    {
        if(buildings[i][2] == buildings[i+1][2]){ continue; }  // new coords are introduced only when height changes
        if(buildings[i+1][0] - buildings[i][1] > 0)  // if there is a gap separating two consecutive buildings
        {  
            skyline.push_back( {buildings[i][1], 0} );  // insert the ground-level coord
            skyline.push_back( {buildings[i+1][0], buildings[i+1][2]} );  // insert the coord from the second building
            continue;  // continue with pairwise comparisons, starting with the first building after the gap
        }
        // y coord is always given by height of second building in the pairwise comparison,
        // x coord depends on whether first or second building is the taller of the two
        (buildings[i][2] < buildings[i+1][2])
        ? skyline.push_back( {buildings[i+1][0], buildings[i+1][2]} )
        : skyline.push_back( {buildings[i][1], buildings[i+1][2]} );
    }
    skyline.push_back( {buildings[len-1][1],0} );  // insert the terminating ground-level coord
    return skyline;
}