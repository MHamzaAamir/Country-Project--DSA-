#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "hashtable.h"
#include "graph.h"
#include "tree.h"

using namespace std;

class countryparser
{
public:
	ifstream file;
	string filename = "countries.csv";


	countryparser()
	{
		string line;
		file.open(filename);
		getline(file, line);		// skip first record which are just column names
	}


	country* seperate_columns(string line)
	{
		int index = 0;
		string word = "";
		int count = 1;
		country* newcountry = new country;

		for (int i = 0; i < line.length() + 1; i++)
		{
			if ((line[i] != ',') && (i != line.length()))
			{
				word += line[i];
			}
			else
			{
				if (count == 1)
				{
					newcountry->countryname = word;
				}
				else if (count == 2)
				{
					newcountry->reigon = word;
				}
				else if (count == 3)
				{
					newcountry->population = stoi(word);
				}
				else if (count == 4)
				{
					newcountry->area = stoi(word);
				}
				else if (count == 5)
				{
					newcountry->population_density = stoi(word);
				}
				else if (count == 6)
				{
					newcountry->coast_area_ratio = stof(word);
				}
				count++;
				word = "";
			}
		}
		return newcountry;
	}
};

class neighbourparser
{
public:
	fstream file;

	neighbourparser()
	{
		string line;
		file.open("neighbours.csv");
		getline(file, line);		//skip first record which are just column names
	}

	void seprate_columns(string line,string* firstcountryname, string* secondcountryname)
	{
		int index = 0;
		int count = 1;
		string word = "";
		

		for (int i = 0; i < line.length() + 1; i++)
		{
			if ((line[i] != ',') && (i != line.length()))
			{
				word += line[i];
			}
			else
			{
				if (count == 2)
				{
					*(firstcountryname) = word;
						
				}
				else if (count == 4)
				{
					*(secondcountryname) = word;
				}
				word = "";
				count++;
			}
		}
	}
};


country* makeAVLtree(NameTree& mytree, country** namearray, int start, int end)
{
	if (start > end)
	{
		return NULL;
	}
	else
	{

		int mid = (start + end) / 2;

		country* root = namearray[mid];

		root->left = makeAVLtree(mytree, namearray, start, mid - 1);

		root->right = makeAVLtree(mytree, namearray, mid + 1, end);

		return root;
	}

}


void parse_neighbourfile_and_connectNodes(graph mygraph)
{
	neighbourparser myparser;
	string* firstcountryname = new string;
	string* secondcountryname = new string;
	string line;

	while (true)
	{
		getline(myparser.file, line);
		if (line == "")
		{
			break;
		}
		myparser.seprate_columns(line, firstcountryname, secondcountryname);

		if (*secondcountryname == "")
		{
			continue;
		}
		country* firstcountry = mygraph.countryhash.getfromHashTable(*firstcountryname);
		country* secondcountry = mygraph.countryhash.getfromHashTable(*secondcountryname);

		mygraph.addEdge(firstcountry, secondcountry);
	}
}


void parse_countryfile_and_addnode(graph& mygraph, NameTree& mytree)
{
	int i = 0;
	string line;
	countryparser mycountryparser;
	country* newcountry = NULL;
	mygraph.countryhash.destroy();
	mytree.destroy();
	while (!mycountryparser.file.eof())
	{
		getline(mycountryparser.file, line);
		if (line == "")
		{
			break;
		}
		newcountry = mycountryparser.seperate_columns(line);
		mygraph.addNode(newcountry);

		mytree.root = insertRecursive(mytree.root, newcountry);
	}
	mycountryparser.file.close();
}

