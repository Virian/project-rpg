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
	vector<Item> backpack;

public:
	Equipment();
	~Equipment();
};
