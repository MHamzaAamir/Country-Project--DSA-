#include <iostream>
#include "parser.h"
#include "graph.h"
#include "tree.h"


using namespace std;

graph countrygraph;
NameTree countrynametree;

void CountryMenu()
{
	int choice;
	string source;
	cout << "1. Search Country By Name:" << endl;
	cout << "2. Print Countries By Reigon:" << endl;
	cin >> choice;
	cin.ignore();
	if (choice == 1)
	{
		cout << "Enter Country:" << endl;
		getline(cin, source);
		searchTreeByName(countrynametree.root,source);
	}
	else if (choice == 2)
	{
		cout << "Enter Region:" << endl;
		getline(cin, source);
		printByReigon(countrynametree.root,source);
	}
}

void NeightboursMenu()
{
	int choice;
	cout << "1. Find Path Between Countries" << endl;
	cout << "2. Find Names Of Neighbours" << endl;
	cout << "3. Find All Reachable Nodes" << endl;
	cin >> choice;
	cin.ignore();
	string source;
	string destination;
	if (choice == 1)
	{
		cout << "Enter Source Country:" << endl;
		getline(cin, source);
		cout << "Enter Destination Country:" << endl;
		getline(cin, destination);
		make_Minimum_Tree(countrygraph, source);
		check_if_land_route_exists(countrygraph, source, destination);
		showpath(countrygraph);
	}
	else if (choice == 2)
	{
		cout << "Enter Country:" << endl;
		getline(cin, source);
		print_neighbours_of_country(countrygraph, source);
	}
	else if (choice == 3)
	{
		cout << "Enter Country:" << endl;
		getline(cin, source);
		make_Minimum_Tree(countrygraph, source);
		print_all_reachable_nodes(countrygraph, source);
	}
}


int Menu()
{
	int choice;
	cout << endl;
	cout << "1. Search About a Country's Information and Reigon" << endl;
	cout << "2. Search About a Country Paths and its Neighbours" << endl;
	cout << "3. Exit" << endl;
	cin >> choice;
	if (choice == 1)
	{
		CountryMenu();
	}
	else if (choice == 2)
	{
		NeightboursMenu();
	}
	else if (choice == 3)
	{
		// DO NOTHING
	}else
	{
		cout << "Incorrect Choice" << endl;
	}
	return choice;

}

void Startup()
{
	cout << "Country Project\n";
	cout << "Made by:\n";
	cout << "Muhammad Hamza Aamir\n";
	cout << "Anqia Tufail\n";
	cout << "Refer to the Readme File for more information on How to use !\n";

}


int main()
{

	Startup();
	int choice = 0;

	while (choice != 3)
	{
		choice = 0;
		parse_countryfile_and_addnode(countrygraph, countrynametree);
		parse_neighbourfile_and_connectNodes(countrygraph);
		choice = Menu();
	}

	
	

}





