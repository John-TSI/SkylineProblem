// https://leetcode.com/problems/the-skyline-problem/

#include<iostream>
#include"../inc/solution.hpp"


void PrintSkyline(std::vector<std::vector<int>>&& skyline)
{
	for(auto coords : skyline)
	{
		std::cout << '[';
		for(int i : coords){ std::cout << i << " "; }
		std::cout << "]\n";
	}
}

int main()
{
	std::vector<std::vector<int>> buildings{{2,9,10},{3,7,15},{5,12,12}};
	PrintSkyline(Solution().getSkyline(buildings));  // [2,10],[3,15],[7,12],[12,0]

	//std::vector<std::vector<int>> buildings2{{0,2,3},{2,5,3}};
	//PrintSkyline(Solution().getSkyline(buildings2));  // [0,3],[5,0]

	//std::vector<std::vector<int>> buildings3{{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
	//PrintSkyline(Solution().getSkyline(buildings3));  // [2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]
	return 0;
}

