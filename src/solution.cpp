#include<algorithm>
#include"../inc/solution.hpp"


// note: each vector<int> B represents a building: B[0] is left x coord, B[1] is right x coord, B[2] is y coord (height)
std::vector<std::vector<int>> Solution::getSkyline(std::vector<std::vector<int>>& buildings)
{
    std::vector<std::vector<int>> walls{}, skyline{};
    std::vector<int> heights{0};
    for(auto b : buildings)
    {
        walls.push_back( {b[0], b[2], 1});  // insert {x coord of left wall, height, tag = 1}
        walls.push_back( {b[1], b[2], 0});  // insert {x coord of right wall, height, tag = 0}
    }
    // sort walls by ascending x coord
    std::sort(walls.begin(), walls.end(), [](const auto& c1, const auto& c2){ return c1[0] < c2[0]; } );

    // sort coinciding walls to ensure they are processed in the correct order
    for(int i{0}; i<walls.size()-1; ++i)
    {
        if(walls[i][0] == walls[i+1][0])
        { 
            // both are left walls of their respective buildings (tagged with 1), ensure taller wall is processed first
            if(walls[i][2] && walls[i+1][2] && walls[i][1] < walls[i+1][1]){ std::swap(walls[i], walls[i+1]); }

            // both are right walls of their respective buildings (tagged with 0), ensure lower wall is processed first
            else if(!walls[i][2] && !walls[i+1][2] && walls[i][1] > walls[i+1][1]){ std::swap(walls[i], walls[i+1]); }

            // a left and right wall coincide, ensure left wall is processed first
            else{ if(walls[i][2] < walls[i+1][2]){ std::swap(walls[i], walls[i+1]); } }
        }
    }

    // begin processing walls: idea is to keep track of heights encountered as we reach each wall, in particular the highest
    int maxHeight{0};
    for(int i{0}; i<walls.size(); ++i)
    {
        if(walls[i][2]) // left wall: start of new building and potentially a contributor to skyline
        { 
            heights.push_back(walls[i][1]); 
            // if left wall is higher than current maxHeight, it is guaranteed to be part of skyline
            if(walls[i][1] > maxHeight){ maxHeight = walls[i][1]; skyline.push_back( {walls[i][0], maxHeight} ); }
        }
        else // right wall: end of a building, need to determine whether it removes current maxHeight from encountered heights vector
        {
            int tmp{maxHeight};  // store current maxHeight
            heights.erase( std::find(heights.begin(), heights.end(), walls[i][1]) );  // remove height of wall from the heights vec
            maxHeight = *std::max_element(heights.begin(), heights.end());
            // if recomputed maxHeight has changed, then the right wall was end of current tallest building.
            // next significant skyline point is then {x coord of the current wall, height of next tallest building}
            if(maxHeight != tmp){ skyline.push_back( {walls[i][0], maxHeight} );  }
        }
    }
    return skyline;
}