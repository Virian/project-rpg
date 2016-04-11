#include "Equipment.h"

Equipment::Equipment()
{
	potionCount = 0;
	Item* temp1 = new Weapon();
	Item* temp2 = new Armor();
	Item* temp3 = new Armor();
	Item* temp4 = new Armor();
	Item* temp5 = new Armor();
	Item* temp6 = new Armor();
	Item* temp7 = new Weapon();
	Item* temp8 = new Weapon();
	Item* temp9 = new Weapon();

	backpack.push_back(temp1);
	backpack.push_back(temp2);
	backpack.push_back(temp3);
	backpack.push_back(temp4);
	backpack.push_back(temp5);
	backpack.push_back(temp6);
	backpack.push_back(temp7);
	backpack.push_back(temp8);
	backpack.push_back(temp9);
}

Equipment::~Equipment()
{
	
}

vector<Item*> Equipment::getBackpack()
{
	return backpack;
}

void Equipment::addItem(Item* newItem)
{
	backpack.push_back(newItem);
}

void Equipment::clearBackpack()
{
	for (size_t i = 0; i < backpack.size(); ++i)
	{
		delete backpack[i];
	}
	backpack.clear();
}

void Equipment::deleteItem(short position)
{
	delete backpack[position];
	backpack.erase(backpack.begin() + position);
}