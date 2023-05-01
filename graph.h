#pragma once
#include <iostream>
#include "parser.h"
#include<string>
#include <iterator>
#include <stack>
#include <queue>

using namespace std;



class graph
{
public:
	stack <country*> pathstack;

	hashtable countryhash;


	void addNode(country* newcountry)
	{
		countryhash.insertInTable(newcountry);
	}

	void addEdge(country* firstcountry, country* secondcountry)
	{
		firstcountry->neighbours.insert(secondcountry);
	}

	void removeEdge(country* firstcountry, country* secondcountry)
	{
		firstcountry->neighbours.erase(secondcountry);
	}

	void resetVisitsAndPredecessors()
	{
		country* loc;
		for (int i = 0; i < 250; i++)
		{
			if (countryhash.heads[i] != NULL)
			{
				loc = countryhash.heads[i];
				while (loc != NULL)
				{
					loc->visited = false;
					loc->predecessor = NULL;
					loc = loc->next;
				}
			}
		}
	}

	

};


bool check(graph& mygraph, country* sourcecountry, country* destinationcountry)
{
	set <country*> ::iterator ptr;

	bool path_exists = false;

	if (sourcecountry == NULL)
	{
		return false;
	}
	if (destinationcountry == NULL)
	{
		return false;
	}
	if (sourcecountry->visited == true)
	{
		return false;
	}
	if (sourcecountry == destinationcountry)
	{
		mygraph.pathstack.push(sourcecountry);
		return true;
	}

	sourcecountry->visited = true;

	for (ptr = sourcecountry->neighbours.begin(); ptr != sourcecountry->neighbours.end(); ptr++)
	{
		if (check(mygraph ,*ptr, destinationcountry))
		{
			path_exists = true;
		}
	}

	if (path_exists)
	{
		mygraph.pathstack.push(sourcecountry);
	}

	return path_exists;


}
bool check_if_land_route_exists(graph& mygraph, string source, string destination)	//wrapper function
{
	country* destinationcountry = mygraph.countryhash.getfromHashTable(destination);
	country* sourcecountry = mygraph.countryhash.getfromHashTable(source);
	bool path_exists = check(mygraph,sourcecountry, destinationcountry);
	mygraph.resetVisitsAndPredecessors();
	return path_exists;
}

void makeMinimumTree(graph& mygraph, string rootName)
{

	set<country*>::iterator ptr;
	country* root = mygraph.countryhash.getfromHashTable(rootName);
	country* ploc = NULL;
	country* loc = NULL;


	if (root == NULL)
	{
		return;
	}

	queue <country*> nodeque;

	nodeque.push(root);
	root->visited = true;

	while (!nodeque.empty())
	{
		loc = nodeque.front();
		nodeque.pop();

		for (ptr = loc->neighbours.begin(); ptr != loc->neighbours.end(); )
		{
			if (!(*ptr)->visited)
			{
				nodeque.push((*ptr));
				(*ptr)->predecessor = loc;
				(*ptr)->visited = true;
				++ptr;
			}
			else
			{
				if (*ptr != loc->predecessor)
				{
					mygraph.removeEdge((*ptr), loc);
					mygraph.removeEdge(loc, (*ptr++));
				}
				else
				{
					++ptr;
				}
			}

		}
	}

}
void make_Minimum_Tree(graph& mygraph, string rootName)
{
	makeMinimumTree(mygraph, rootName);
	mygraph.resetVisitsAndPredecessors();
}

void showpath(graph mygraph)
{
	string name;
	while (!mygraph.pathstack.empty())
	{
		name = mygraph.pathstack.top()->countryname;
		mygraph.pathstack.pop();
		if (mygraph.pathstack.empty())
		{
			break;
		}
		cout << name << " -> ";
	}
	cout << name << endl;

}

void print_neighbours_of_country(graph mygraph,string countryname)
{
	country* thiscountry = mygraph.countryhash.getfromHashTable(countryname);
	set<country*>::iterator ptr;

	for (ptr = thiscountry->neighbours.begin(); ptr != thiscountry->neighbours.end(); ptr++)
	{
		cout << (*ptr)->countryname << ",";
	}
	cout << endl;
}

void printallreachablenodes(country* countryname)
{
	set <country*> ::iterator ptr;
	for(ptr = countryname->neighbours.begin(); ptr != countryname->neighbours.end(); ptr++)
	{
		if (!(*ptr)->visited)
		{
			(*ptr)->visited = true;
			cout << (*ptr)->countryname << endl;
			printallreachablenodes(*ptr);
		}
	}	
}
void print_all_reachable_nodes(graph mygraph, string countryname)
{
	country* country = mygraph.countryhash.getfromHashTable(countryname);
	printallreachablenodes(country);
	mygraph.resetVisitsAndPredecessors();
}