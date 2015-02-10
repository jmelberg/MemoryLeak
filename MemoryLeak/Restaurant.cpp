// Program: Restaurant
// Name: Inderjit Bassi
// Date: 6/13/14
// .cpp for restaurant header

#include "Restaurant.h"
bool Restaurant::operator > (const Restaurant &obj) const
{
		int holdSize1 = static_cast<int>(restaurant.size());
		int holdSize2 = static_cast<int>(obj.restaurant.size());
		int holdSize = holdSize1;
		
		if (holdSize1 < holdSize2)
		{
			holdSize = holdSize2;
		}

		string name1 = restaurant;
		string name2 = obj.restaurant;

		for (int i = 0; i < holdSize; i++)
		{
			if (i < holdSize1)
				name1[i] = tolower(name1[i]);
			if (i < holdSize2)
				name2[i] = tolower(name2[i]);
		}

		if (name1 > name2)
			return true;
		else
			return false;
}

bool Restaurant::operator < (const Restaurant &obj) const
{
		int holdSize1 = static_cast<int>(restaurant.size());
		int holdSize2 = static_cast<int>(obj.restaurant.size());
		int holdSize = holdSize1;
		
		if (holdSize1 < holdSize2)
		{
			holdSize = holdSize2;
		}

		string name1 = restaurant;
		string name2 = obj.restaurant;

		for (int i = 0; i < holdSize; i++)
		{
			if (i < holdSize1)
				name1[i] = tolower(name1[i]);
			if (i < holdSize2)
				name2[i] = tolower(name2[i]);
		}

		if (name1 < name2)
			return true;
		else
			return false;
}

bool Restaurant::operator == (const Restaurant&obj) const
{
		int holdSize1 = static_cast<int>(restaurant.size());
		int holdSize2 = static_cast<int>(obj.restaurant.size());
		int holdSize = holdSize1;
		
		if (holdSize1 < holdSize2)
		{
			holdSize = holdSize2;
		}

		string name1 = restaurant;
		string name2 = obj.restaurant;

		for (int i = 0; i < holdSize; i++)
		{
			if (i < holdSize1)
				name1[i] = tolower(name1[i]);
			if (i < holdSize2)
				name2[i] = tolower(name2[i]);
		}

		if (name1 == name2)
			return true;
		else
			return false;
}