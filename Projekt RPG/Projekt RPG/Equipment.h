#pragma once
#include "Item.h"
#include <vector>

class Equipment
{
private:
	Weapon* activeWeapon;					/*aktywna bron*/
	Armor* activeArmor;						/*aktywna zbroja*/
	std::vector<Item*> backpack;			/*kontener przedmiotow w plecaku*/
	short potionCount;						/*licznik mikstur*/
public:
	static const int backpackSize = 10;		/*maksymalna ilosc przedmiotow w plecaku*/
	Equipment();
	~Equipment();
	std::vector<Item*> getBackpack();		/*zwraca plecak*/
	Weapon* getActiveWeapon();				/*zwraca aktywna bron*/
	Armor* getActiveArmor();				/*zwraca aktywna zbroje*/
	void addItem(Item*);					/*dodaje przedmiot do plecaka*/
	void clearBackpack();					/*czysci plecak oraz aktywny ekwipunek*/
	void deleteItem(short);					/*usuwa konkretny przedmiot z ekwipunku*/
	void swapActiveItem(short);				/*zamienia przedmiot z plecaka z aktywnym przedmiotem lub zdejmuje aktywny przedmiot do plecaka*/
	unsigned short usePotion();				/*dekrementuje licznik mikstur, zwraca 0 jesli udalo sie uzyc mikstury (wczesniej byla przynajmniej 1) lub 1 jesli nie udalo sie jej uzyc (wczesniej bylo 0)*/
	short getPotionCount();					/*zwraca licznik mikstur*/
	void setPotionCount(short);				/*ustawia licznik mikstur na zadana wartosc*/
	void addPotion();						/*inkrementuje licznik mikstur*/
};