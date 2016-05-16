#pragma once
#include "Item.h"
#include <vector>

using namespace std;

class Equipment
{
private:
	Weapon* activeWeapon;
	Armor* activeArmor;
	vector<Item*> backpack;
	short potionCount;
public:
	static const int backpackSize = 10;
	Equipment();
	~Equipment();
	vector<Item*> getBackpack();
	Weapon* getActiveWeapon();
	Armor* getActiveArmor();
	void addItem(Item*);
	void clearBackpack();
	void deleteItem(short);
	void swapActiveItem(short);
	unsigned short usePotion();
	short getPotionCount();
	void addPotion();
};
