#pragma once
#include <iostream>
#include <set>
using namespace std;

class country
{
public:
	string countryname;
	string reigon;
	int population;
	int area;
	int population_density;
	float coast_area_ratio;

	//Using this for seperate chaining in hashtable
	country* next;			

	//Using this for Graphs 
	set <country*> neighbours; 
	bool visited;
	country* predecessor;

	//Using this for AVL tree
	country* left;
	country* right;



	country()
	{
		countryname = "";
		reigon = "";
		population = 0;
		area = 0;
		population_density = 0;
		coast_area_ratio = 0;

		// For Hash Table
		next = NULL;

		// For Graph		
		visited = false;
		predecessor = NULL;

		// For  AVLTree
		left = NULL;
		right = NULL;
	}
};