#pragma once
#include "Item.h"
#include <vector>

using namespace std;

const int backpackSize = 10;

class Equipment
{
private:
	Weapon activeWeapon;
	Armor activeArmor;
	vector<Item*> backpack;
	short potionCount;
public:
	Equipment();
	~Equipment();
	vector<Item*> getBackpack();
	void addItem(Item*);
	void clearBackpack();
	void deleteItem(short);
};
