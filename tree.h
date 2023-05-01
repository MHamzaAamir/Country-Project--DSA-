#pragma once
#include "country.h"


class NameTree
{
public:
	country* root = NULL;
	country* loc = NULL;
	country* ploc = NULL;

	bool isempty()
	{
		return (root == NULL);
	}

	void insert(country* value)
	{
		if (isempty())
		{
			root = value;
		}
		else
		{
			search(value);
			if (loc == NULL)
			{
				if (value->countryname > ploc->countryname)
				{
					ploc->right = value;
				}
				else
				{
					ploc->left = value;
				}
			}
		}
	}

	void search(country* value)
	{
		ploc = NULL;
		loc = root;
		while (loc != NULL && loc->countryname != value->countryname)
		{
			ploc = loc;
			if (loc->countryname < value->countryname)
			{
				loc = loc->right;
			}
			else
			{
				loc = loc->left;
			}
		}
	}

	void destroy()
	{
		country* loc = root;
		country* ploc = NULL;

		while (loc != NULL)
		{
			ploc = loc;
			loc = loc->next;
			delete ploc;
		}
		root = NULL;

	}

	void searchbyname(string countryname)
	{
		ploc = NULL;
		loc = root;
		while (loc != NULL && loc->countryname != countryname)
		{
			ploc = loc;
			if (loc->countryname < countryname)
			{
				loc = loc->right;
			}
			else
			{
				loc = loc->left;
			}
		}

		if (loc != NULL)
		{
			cout << loc->countryname << " " << loc->reigon << endl;
		}
	}

};



void inOrder(country* root)
{
	if (root != NULL) {
		inOrder(root->left);
		
		cout << root->countryname << endl;
		inOrder(root->right);
	}
}


country* leftRotate(country* root)
{
	country* child = root->right;


	if (child != NULL)
	{
		root->right = child->left;
		child->left = root;
	}
	return child;

}
country* rightRotate(country* root)
{
	country* child = root->left;

	if (child != NULL)
	{
		root->left = child->right;
		child->right = root;
	}
	return child;
}



void searchTreeByName(country* root, string countryname)
{
	if (root == NULL)
	{
		cout << "NOT FOUND" << endl;

	}
	else if (root->countryname == countryname)
	{
		cout << "Country Name: " << root->countryname << endl;
		cout << "Reigon: " << root->reigon << endl;
		cout << "Population: " << root->population << endl;
		cout << "Area: " << root->area << endl;
		cout << "Population Density: " << root->population_density << endl;
		cout << "Coast / Area Ratio: " << root->coast_area_ratio << endl;
	}
	else if (root->countryname < countryname)
	{
		searchTreeByName(root->right, countryname);
	}
	else if (root->countryname > countryname)
	{
		searchTreeByName(root->left, countryname);
	}
}



void printByReigon(country* root, string reigon)
{
	if (root == NULL)
	{
		return;
	}
	size_t found = root->reigon.find(reigon);
	if (found != string::npos)
	{
		cout << root->countryname  << " : " << root->reigon << endl;
	}
	printByReigon(root->left, reigon);
	printByReigon(root->right, reigon);
}


int heightoftree(country* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return max(heightoftree(root->left), heightoftree(root->right)) + 1;
}

int BalanceFactor(country* root)
{
	return (heightoftree(root->left) - heightoftree(root->right));
}

bool isAVL(country* root)
{
	if (root == NULL)
	{
		return true;
	}
	if (((heightoftree(root->left) - heightoftree(root->right)) == 1) || ((heightoftree(root->left) - heightoftree(root->right)) == 0) || ((heightoftree(root->left) - heightoftree(root->right)) == -1))
	{
		return (isAVL(root->left) && isAVL(root->right));;
	}
	else
	{
		return false;
	}
}


country* insertRecursive(country* root, country* newcountry)
{
	if (root == NULL)
	{
		return newcountry;
	}
	if (newcountry->countryname < root->countryname)
	{
		root->left = insertRecursive(root->left, newcountry);
	}
	else
	{
		root->right = insertRecursive(root->right, newcountry);
	}

	if (BalanceFactor(root) > 1)
	{
		if (root->left->countryname > newcountry->countryname)
		{
			// FULL RIGHT
			root = rightRotate(root);
		}
		else
		{
			// LEFT RIGHT
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}

	}
	else if (BalanceFactor(root) < -1)
	{
		if (root->right->countryname < newcountry->countryname)
		{
			//FULL LEFT
			root = leftRotate(root);
		}
		else
		{
			// RIGHT LEFT
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
	}

	return root;
}