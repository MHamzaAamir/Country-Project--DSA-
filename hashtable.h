#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "country.h"
#include "parser.h"

using namespace std;


class hashtable
{
public:
	country** heads;
	int location;

	hashtable()
	{
		heads = new country * [250] {NULL};
	}

	void insertInTable(country* countryname)
	{
		location = hashfunction(countryname->countryname);

		if (heads[location] == NULL)
		{
			heads[location] = countryname;
		}
		else
		{
			country* ploc = heads[location];
			country* loc = heads[location]->next;
			while (loc != NULL)
			{
				ploc = loc;
				loc = loc->next;
			}
			ploc->next = countryname;
		}
	
	}

	int hashfunction(string countryname)
	{
		int strlen = countryname.length();
		long long int hash = 11;

		for (int i = 0; i < strlen; i++)
		{
			hash = hash * 3 + countryname[i];
		}
		location = hash % 250;
		return location;
	}

	country* getfromHashTable(string countryname)
	{
		location = hashfunction(countryname);

		country* loc = heads[location];

		while((loc != NULL) && (loc->countryname != countryname))
		{ 
			loc = loc->next;
		}
		return loc;
	}

	void destroy()
	{
		for (int i = 0; i < 250; i++)
		{
			delete heads[i];
			heads[i] = NULL;
		}
	}
};
