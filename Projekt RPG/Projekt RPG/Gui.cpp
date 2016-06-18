#include "Gui.h"
#include <Windows.h>

Gui::Gui()
{	
	font.loadFromFile("fonts/game_over.ttf"); /*wczytanie czcionki*/
	/*ustawienie parametrow tekstow*/
	currHp.setFont(font);
	currHp.setCharacterSize(90);
	maximHp.setFont(font);
	maximHp.setCharacterSize(45);
	experience.setFont(font);
	experience.setCharacterSize(100);
	potions.setFont(font);
	potions.setCharacterSize(70);
	texture.loadFromFile("images/tilesheet.png"); /*wczytanie tekstury*/
	/*ustawienie obrazkow czesci widocznej przez caly czas*/
	hpGauge.setTexture(texture);
	hpGauge.setTextureRect(sf::IntRect(0, 1024, 128, 128));
	expGauge.setTexture(texture);
	expGauge.setTextureRect(sf::IntRect(0, 896, 128, 128));
	skill1.setSize(sf::Vector2f(64, 64));
	skill2.setSize(sf::Vector2f(64, 64));
	skill3.setSize(sf::Vector2f(64, 64));

	skill1.setTexture(&texture);
	skill2.setTexture(&texture);
	skill3.setTexture(&texture);
	fadedSkill1.setTexture(&texture);
	fadedSkill2.setTexture(&texture);
	fadedSkill3.setTexture(&texture);

	flash.restart(); /*wystartowanie clocka*/
	/*ustawienie obrazkow z menu pauzy*/
	pauseMenu.setSize(sf::Vector2f(350, 450));
	resumeButton.setSize(sf::Vector2f(320, 100));
	saveButton.setSize(sf::Vector2f(320, 100));
	quitButton.setSize(sf::Vector2f(320, 100));
	
	pauseMenu.setFillColor(sf::Color::Black);
	pauseMenu.setOutlineThickness(-2);
	pauseMenu.setOutlineColor(sf::Color::White);
	resumeButton.setTexture(&texture);
	resumeButton.setTextureRect(sf::IntRect(0, 384, 320, 100));
	saveButton.setTexture(&texture);
	saveButton.setTextureRect(sf::IntRect(0, 384, 320, 100));
	quitButton.setTexture(&texture);
	quitButton.setTextureRect(sf::IntRect(0, 384, 320, 100));
	/*ustawienie parametrow tekstow z menu pauzy*/
	resume.setFont(font);
	resume.setCharacterSize(90);
	resume.setString("RESUME");
	save.setFont(font);
	save.setCharacterSize(90);
	save.setString("SAVE GAME");
	quit.setFont(font);
	quit.setCharacterSize(90);
	quit.setString("QUIT");
	/*ustawienie obrazkow z menu ekwipunku*/
	backpackBackground.setSize(sf::Vector2f(680, 296));
	activeEquipment.setSize(sf::Vector2f(300, 440));
	characterInfo.setSize(sf::Vector2f(680, 360));
	itemInfo.setSize(sf::Vector2f(300, 216));
	plus.setSize(sf::Vector2f(20, 20));
	
	backpackSlot.setTexture(texture);
	backpackSlot.setTextureRect(sf::IntRect(0, 768, 128, 128));
	activeBackpackSlot.setTexture(texture);
	activeBackpackSlot.setTextureRect(sf::IntRect(128, 768, 128, 128));
	plus.setTexture(&texture);
	plus.setTextureRect(sf::IntRect(0, 484, 20, 20));

	backpackBackground.setFillColor(sf::Color::Black);
	backpackBackground.setOutlineThickness(-2);
	backpackBackground.setOutlineColor(sf::Color::White);
	activeEquipment.setFillColor(sf::Color::Black);
	activeEquipment.setOutlineThickness(-2);
	activeEquipment.setOutlineColor(sf::Color::White);
	characterInfo.setFillColor(sf::Color::Black);
	characterInfo.setOutlineThickness(-2);
	characterInfo.setOutlineColor(sf::Color::White);
	itemInfo.setFillColor(sf::Color::Black);
	itemInfo.setOutlineThickness(-2);
	itemInfo.setOutlineColor(sf::Color::White);
	/*ustawienie parametrow tekstow z menu ekwipunku*/
	activeEquipmentHeader.setFont(font);
	activeEquipmentHeader.setCharacterSize(80);
	activeEquipmentHeader.setStyle(sf::Text::Bold);
	activeEquipmentHeader.setString("Active equipment");
	characterInfoHeader.setFont(font);
	characterInfoHeader.setCharacterSize(80);
	characterInfoHeader.setStyle(sf::Text::Bold);
	characterInfoHeader.setString("Character information");
	itemInfoHeader.setFont(font);
	itemInfoHeader.setCharacterSize(80);
	itemInfoHeader.setStyle(sf::Text::Bold);
	itemInfoHeader.setString("Item information");

	playerStats.setFont(font);
	playerStats.setCharacterSize(55);
	itemStats.setFont(font);
	itemStats.setCharacterSize(55);
	activeEquipmentInfo.setFont(font);
	activeEquipmentInfo.setCharacterSize(65);
	/*ustawienie obrazkow z menu zmiany poziomu*/
	levelMenu.setSize(sf::Vector2f(350, 550));
	levelMenu.setFillColor(sf::Color::Black);
	levelMenu.setOutlineThickness(-2.f);
	levelMenu.setOutlineColor(sf::Color::White);
	/*ustawienie parametrow tekstow z menu zmiany poziomu*/
	sf::Text header;
	sf::Text information;
	sf::Text option1, option2, option3, option4, option5;
	header.setString("Choose level:");
	information.setString("Press ESC to go back.");
	option1.setString("1 - Level1");
	option2.setString("2 - Level2");
	option3.setString("3 - Level3");
	option4.setString("4 - Level4");
	option5.setString("5 - Level5");
	levelOptions.push_back(header);
	levelOptions.push_back(option1);
	levelOptions.push_back(option2);
	levelOptions.push_back(option3);
	levelOptions.push_back(option4);
	levelOptions.push_back(option5);
	levelOptions.push_back(information);
	for (size_t i = 0; i < levelOptions.size(); ++i)
	{
		levelOptions[i].setFont(font);
		levelOptions[i].setCharacterSize(70);
	}
}

Gui::~Gui()
{
	/*wyczyszczenie kontenerow*/
	for (size_t i = 0; i < damageInfo.size(); ++i)
	{
		delete damageInfo[i];
	}
	damageInfo.clear();
	for (size_t i = 0; i < hpInfo.size(); ++i)
	{
		delete hpInfo[i];
	}
	hpInfo.clear();
}

Gui::HpBar::HpBar()
{
	currentHp.setFillColor(sf::Color::Red); /*obecne hp ma kolor czerwony*/
	missingHp.setFillColor(sf::Color(120, 0, 0)); /*brakujace hp ma kolor ciemnoczerwony*/
}

void Gui::setSkillPictures(std::string className)
{
	/*ustawienie roznych obrazkow w zaleznosci od klasy postaci*/
	if (className == "Soldier")
	{
		skill1.setTextureRect(sf::IntRect(0, 1152, 64, 64));
		fadedSkill1.setTextureRect(sf::IntRect(64, 1152, 64, 64));
		skill2.setTextureRect(sf::IntRect(128, 1152, 64, 64));
		fadedSkill2.setTextureRect(sf::IntRect(192, 1152, 64, 64));
		skill3.setTextureRect(sf::IntRect(256, 1152, 64, 64));
		fadedSkill3.setTextureRect(sf::IntRect(320, 1152, 64, 64));
	}
	else if (className == "Sentinel")
	{
		skill1.setTextureRect(sf::IntRect(0, 1216, 64, 64));
		fadedSkill1.setTextureRect(sf::IntRect(64, 1216, 64, 64));
		skill2.setTextureRect(sf::IntRect(128, 1216, 64, 64));
		fadedSkill2.setTextureRect(sf::IntRect(192, 1216, 64, 64));
		skill3.setTextureRect(sf::IntRect(256, 1216, 64, 64));
		fadedSkill3.setTextureRect(sf::IntRect(320, 1216, 64, 64));
	}
	else
	{
		skill1.setTextureRect(sf::IntRect(0, 1280, 64, 64));
		fadedSkill1.setTextureRect(sf::IntRect(64, 1280, 64, 64));
		skill2.setTextureRect(sf::IntRect(128, 1280, 64, 64));
		fadedSkill2.setTextureRect(sf::IntRect(192, 1280, 64, 64));
		skill3.setTextureRect(sf::IntRect(256, 1280, 64, 64));
		fadedSkill3.setTextureRect(sf::IntRect(320, 1280, 64, 64));
	}
}

void Gui::drawScreen(sf::RenderWindow &window, Player* player)
{
	short currentHp = player->getHp();
	short maxHp = player->getMaxHp();
	unsigned exp = player->getExp();
	unsigned expForNextLevel = player->getExpForNextLevel();
	/*sprawdzenie calego kontenera informacji o zadanych/wyleczonych obrazeniach*/
	for (size_t i = 0; i < damageInfo.size(); ++i)
	{
		if (damageInfo[i]->lifeTime.getElapsedTime() > sf::seconds(0.6f)) /*jesli element istnieje za dlugo, zostaje usuniety*/
		{
			delete damageInfo[i];
			damageInfo.erase(damageInfo.begin() + i);
		}
		else
		{
			window.draw(damageInfo[i]->text); /*w przeciwnym wypadku, zostaje narysowany*/
			if (damageInfo[i]->tick.getElapsedTime() > sf::milliseconds(10)) /*aktualizacja napisu moze nastapic tylko co okreslona ilosc czasu*/
			{
				sf::Color tempColor;

				damageInfo[i]->text.move(0.0f, -1.0f); /*przesuniecie tekstu w gory*/
				/*efekt zanikania z czasem*/
				tempColor = damageInfo[i]->text.getColor();
				tempColor.a -= 4;
				damageInfo[i]->text.setColor(tempColor);
				damageInfo[i]->tick.restart(); /*reset clocka aktualizacji*/
			}
		}
	}
	/*sprawdzenie calego kontenera paska hp*/
	for (size_t i = 0; i < hpInfo.size(); ++i)
	{
		/*pasek jest wyswietlany na zasadzie [obecne hp][brakujace hp], czyli czesc z brakujacym hp jest dolaczana od razu za czescia z obecnym hp*/
		/*przesuniecie paska troche ponad przeciwnika*/
		hpInfo[i]->currentHp.setPosition(sf::Vector2f(hpInfo[i]->characterPosition.x - 32, hpInfo[i]->characterPosition.y - 24));
		hpInfo[i]->missingHp.setPosition(sf::Vector2f(hpInfo[i]->characterPosition.x - 32 + hpInfo[i]->currentHp.getGlobalBounds().width, hpInfo[i]->characterPosition.y - 24));
		/*narysowanie paska*/
		window.draw(hpInfo[i]->currentHp);
		window.draw(hpInfo[i]->missingHp);
	}
	/*ustawienie odpowiedniego obrazka ilustrujacego obecne hp gracza*/
	float hpPercent = (static_cast<float>(currentHp) / static_cast<float>(maxHp)) * 100.0f;
	if ((hpPercent <= 100) && (hpPercent > 500.0f/6.0f)) hpGauge.setTextureRect(sf::IntRect(0, 1024, 128, 128));
	else if ((hpPercent <= 500.0f / 6.0f) && (hpPercent > 400.0f / 6.0f)) hpGauge.setTextureRect(sf::IntRect(128, 1024, 128, 128));
	else if ((hpPercent <= 400.0f / 6.0f) && (hpPercent > 50)) hpGauge.setTextureRect(sf::IntRect(256, 1024, 128, 128));
	else if ((hpPercent <= 50) && (hpPercent > 200.0f / 6.0f)) hpGauge.setTextureRect(sf::IntRect(384, 1024, 128, 128));
	else if ((hpPercent <= 200.0f / 6.0f) && (hpPercent > 100.0f / 6.0f)) hpGauge.setTextureRect(sf::IntRect(512, 1024, 128, 128));
	else if ((hpPercent <= 100.0f / 6.0f) && (hpPercent > 0))
	{
		/*miganie dla niskiego stanu zdrowia*/
		if (flash.getElapsedTime().asSeconds() > 0.5 && flash.getElapsedTime().asSeconds() <= 1)
			hpGauge.setTextureRect(sf::IntRect(768, 1024, 128, 128));
		else if (flash.getElapsedTime().asSeconds() > 1)
		{
			hpGauge.setTextureRect(sf::IntRect(640, 1024, 128, 128));
			flash.restart();
		}
	}
	/*ustawienie odpowiedniego obrazka ilustrujacego obecne doswiadczenie gracza*/
	float expPercent = (static_cast<float>(exp) / static_cast<float>(expForNextLevel)) * 100.0f;
	if ((expPercent <= 100) && (expPercent > 500.0f / 6.0f)) expGauge.setTextureRect(sf::IntRect(0, 896, 128, 128));
	else if ((expPercent <= 500.0f / 6.0f) && (expPercent > 400.0f / 6.0f)) expGauge.setTextureRect(sf::IntRect(128, 896, 128, 128));
	else if ((expPercent <= 400.0f / 6.0f) && (expPercent > 50)) expGauge.setTextureRect(sf::IntRect(256, 896, 128, 128));
	else if ((expPercent <= 50) && (expPercent > 200.0f / 6.0f)) expGauge.setTextureRect(sf::IntRect(384, 896, 128, 128));
	else if ((expPercent <= 200.0f / 6.0f) && (expPercent > 100.0f / 6.0f)) expGauge.setTextureRect(sf::IntRect(512, 896, 128, 128));
	else if ((expPercent <= 100.0f / 6.0f) && (expPercent >= 0)) expGauge.setTextureRect(sf::IntRect(640, 896, 128, 128));
	/*ustawienie na ekranie pozycji obrazkow reprezentujacych hp i doswiadczenie*/
	hpGauge.setPosition(window.mapPixelToCoords(sf::Vector2i(36, 570)));
	expGauge.setPosition(window.mapPixelToCoords(sf::Vector2i(1116, 570)));
	/*ustawienie tekstow z hp, doswiadczeniem i miksturami*/
	currHp.setString(std::to_string(currentHp));
	maximHp.setString(std::to_string(maxHp));
	experience.setString(std::to_string(static_cast<int>(expPercent)) + "%");
	potions.setString("Potions: " + std::to_string(player->getEquipment()->getPotionCount()));
	/*ustawienie tych tekstow na odpowiedniej pozycji na ekranie*/
	if (currentHp > 99) currHp.setPosition(window.mapPixelToCoords(sf::Vector2i(70, 550))); /*przesuniecie dla roznych ilosci znakow*/
	else if (currentHp <= 99 && currentHp > 9) currHp.setPosition(window.mapPixelToCoords(sf::Vector2i(78, 550)));
	else currHp.setPosition(window.mapPixelToCoords(sf::Vector2i(86, 550)));
	maximHp.setPosition(window.mapPixelToCoords(sf::Vector2i(85, 610)));
	experience.setPosition(window.mapPixelToCoords(sf::Vector2i(1142, 546)));
	potions.setPosition(window.mapPixelToCoords(sf::Vector2i(170, 625)));
	/*rysowanie wszystkiego na ekranie*/
	window.draw(hpGauge);
	window.draw(expGauge);
	window.draw(skill1);
	window.draw(skill2);
	window.draw(skill3);
	window.draw(fadedSkill1);
	window.draw(fadedSkill2);
	window.draw(fadedSkill3);
	currHp.move(sf::Vector2f(2, 2));
	currHp.setColor(sf::Color::Black);
	window.draw(currHp);
	currHp.move(sf::Vector2f(-2, -2));
	currHp.setColor(sf::Color::White);
	window.draw(currHp);
	maximHp.move(sf::Vector2f(2, 2));
	maximHp.setColor(sf::Color::Black);
	window.draw(maximHp);
	maximHp.move(sf::Vector2f(-2, -2));
	maximHp.setColor(sf::Color::White);
	window.draw(maximHp);
	experience.move(sf::Vector2f(2, 2));
	experience.setColor(sf::Color::Black);
	window.draw(experience);
	experience.move(sf::Vector2f(-2, -2));
	experience.setColor(sf::Color::White);
	window.draw(experience);
	potions.move(sf::Vector2f(2, 2));
	potions.setColor(sf::Color::Black);
	window.draw(potions);
	potions.move(sf::Vector2f(-2, -2));
	potions.setColor(sf::Color::White);
	window.draw(potions);
}

void Gui::drawPauseMenu(sf::RenderWindow &window)
{
	/*ustawienie obrazkow na odpowiedniej pozycji*/
	pauseMenu.setPosition(window.mapPixelToCoords(sf::Vector2i(465, 135)));
	resumeButton.setPosition(window.mapPixelToCoords(sf::Vector2i(480, 172)));
	saveButton.setPosition(window.mapPixelToCoords(sf::Vector2i(480, 310)));
	quitButton.setPosition(window.mapPixelToCoords(sf::Vector2i(480, 447)));
	/*ustawienie tekstow na odpowiedniej pozycji*/
	resume.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x / 2 - resume.getGlobalBounds().width / 2), 145)));
	save.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x / 2 - save.getGlobalBounds().width / 2), 283)));
	quit.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x / 2 - quit.getGlobalBounds().width / 2), 420)));
	/*rysowanie na ekranie*/
	window.draw(pauseMenu);
	window.draw(resumeButton);
	window.draw(saveButton);
	window.draw(quitButton);
	window.draw(resume);
	window.draw(save);
	window.draw(quit);
}

void Gui::drawEquipment(sf::RenderWindow &window, Player* player, short position)
{
	std::vector<Item*> backpack;
	Weapon* activeWeapon;
	Armor* activeArmor;
	/*ustawienie kazdego tla na ekranie*/
	backpackBackground.setPosition(window.mapPixelToCoords(sf::Vector2i(120, 398)));
	activeEquipment.setPosition(window.mapPixelToCoords(sf::Vector2i(860, 254)));
	characterInfo.setPosition(window.mapPixelToCoords(sf::Vector2i(120, 26)));
	itemInfo.setPosition(window.mapPixelToCoords(sf::Vector2i(860, 26)));
	/*ustawienie kazdego naglowka na ekranie*/
	activeEquipmentHeader.setPosition(window.mapPixelToCoords(sf::Vector2i(870, 214)));
	characterInfoHeader.setPosition(window.mapPixelToCoords(sf::Vector2i(130, -14)));
	itemInfoHeader.setPosition(window.mapPixelToCoords(sf::Vector2i(870, -14)));
	/*ustawienie tekstu ze statystykami gracza*/
	playerStats.setString("Name: " + player->getName() + "\nClass: " + player->getClassName() + "\nLevel: " + std::to_string(player->getLvl())
		+ "\nExperience: " + std::to_string(player->getExp()) + "\nExperience to level up: " + std::to_string(player->getExpForNextLevel())
		+ "\nStrength: " + std::to_string(player->getStr()) + "\nIntelligence: " + std::to_string(player->getInt()) + "\nAgility: "
		+ std::to_string(player->getAgi()) + "\nAvailable points to spend: " + std::to_string(player->getPointsToSpend()));
	playerStats.setPosition(window.mapPixelToCoords(sf::Vector2i(130, 40)));
	
	backpack = player->getEquipment()->getBackpack();
	activeArmor = player->getEquipment()->getActiveArmor();
	activeWeapon = player->getEquipment()->getActiveWeapon();
	/*wypisanie informacji o odpowiednim przedmiocie*/
	if (position == -1) itemStats.setString("");
	else if ((position == -2) && (activeWeapon != NULL))
	{
		if (activeWeapon->isRanged()) itemStats.setString(activeWeapon->getName() + "\nAttack: " + std::to_string(activeWeapon->getAttackValue()) + "\nRange: Ranged");
		else itemStats.setString(activeWeapon->getName() + "\nAttack: " + std::to_string(activeWeapon->getAttackValue()) + "\nRange: Melee");
	}
	else if ((position == -3) && (activeArmor != NULL)) itemStats.setString(activeArmor->getName() + "\nArmor: " + std::to_string(activeArmor->getArmorValue()));
	else
	{
		if (position < backpack.size())
		{
			Weapon* temp1;
			Armor* temp2;
			if (temp1 = dynamic_cast<Weapon*>(backpack[position]))
			{				
				if (temp1->isRanged()) itemStats.setString(backpack[position]->getName() + "\nAttack: " + std::to_string(temp1->getAttackValue()) + "\nRange: Ranged");
				else itemStats.setString(backpack[position]->getName() + "\nAttack: " + std::to_string(temp1->getAttackValue()) + "\nRange: Melee");
			}
			else if (temp2 = dynamic_cast<Armor*>(backpack[position]))
				itemStats.setString(backpack[position]->getName() + "\nArmor: " + std::to_string(temp2->getArmorValue()));
		}
	}
	itemStats.setPosition(window.mapPixelToCoords(sf::Vector2i(870, 40)));
	/*rysowanie na ekranie*/
	window.draw(backpackBackground);
	window.draw(activeEquipment);
	window.draw(characterInfo);
	window.draw(itemInfo);
	window.draw(activeEquipmentHeader);
	window.draw(characterInfoHeader);
	window.draw(itemInfoHeader);
	window.draw(playerStats);
	window.draw(itemStats);
	if (player->getPointsToSpend() > 0) /*rysowanie plusa jesli sa dostepne punkty do wydania*/
	{
		plus.setPosition(window.mapPixelToCoords(sf::Vector2i(340, 235)));
		window.draw(plus);
		plus.setPosition(window.mapPixelToCoords(sf::Vector2i(340, 265)));
		window.draw(plus);
		plus.setPosition(window.mapPixelToCoords(sf::Vector2i(340, 295)));
		window.draw(plus);
	}

	/*rysowanie miejsc w ekwipunku*/
	for (short i = 0; i < 2; ++i)
	{
		for (short j = 0; j < 5; ++j)
		{
			backpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(140 + j * 128, 418 + i * 128)));
			window.draw(backpackSlot);
		}
	}
	/*rysowanie czesci z aktywnym ekwipunkiem*/
	activeEquipmentInfo.setString("Weapon");
	activeEquipmentInfo.setPosition(window.mapPixelToCoords(sf::Vector2i(960, 264)));
	backpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(946, 340)));
	window.draw(backpackSlot);
	window.draw(activeEquipmentInfo);
	activeEquipmentInfo.setString("Armor");
	activeEquipmentInfo.setPosition(window.mapPixelToCoords(sf::Vector2i(970, 446)));
	backpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(946, 520)));
	window.draw(backpackSlot);
	window.draw(activeEquipmentInfo);
	/*rysowanie aktywnego(badanego) miejsca ekwipunku*/
	if (position >= 0 && position < backpack.size())
	{
		short i, j;
		i = position / 5;
		j = position - i;
		activeBackpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(140 + j * 128, 418 + i * 128)));
	}
	else if (position == -2 && activeWeapon != NULL) activeBackpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(946, 340)));
	else if (position == -3 && activeArmor != NULL) activeBackpackSlot.setPosition(window.mapPixelToCoords(sf::Vector2i(946, 520)));
	if (position != -1) window.draw(activeBackpackSlot);
	/*rysowanie przedmiotow w ekwipunku*/
	for (size_t i = 0, j = 0; i < backpack.size(); ++i)
	{
		if (i == 5) ++j;
		backpack[i]->setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(140 + i * 128 - 5 * j * 128), static_cast<int>(418 + j * 128))));
		window.draw(*backpack[i]);
	}

	if (activeWeapon != NULL)
	{
		activeWeapon->setPosition(window.mapPixelToCoords(sf::Vector2i(946, 340)));
		window.draw(*activeWeapon);
	}
	if (activeArmor != NULL)
	{
		activeArmor->setPosition(window.mapPixelToCoords(sf::Vector2i(946, 520)));
		window.draw(*activeArmor);
	}	
}

void Gui::drawDeathScreen(sf::RenderWindow& window)
{
	/*ustawienie tekstow i ich narysowanie*/
	sf::Text info1("You are dead!", font, 200);
	sf::Text info2("Press ENTER to return to the menu", font, 90);

	info1.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x / 2 - info1.getGlobalBounds().width / 2), 120)));
	info2.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(window.getSize().x / 2 - info2.getGlobalBounds().width / 2), 400)));

	info1.setColor(sf::Color::Black);
	info1.move(sf::Vector2f(4, 4));
	window.draw(info1);
	info1.setColor(sf::Color::White);
	info1.move(sf::Vector2f(-4, -4));
	window.draw(info1);

	info2.setColor(sf::Color::Black);
	info2.move(sf::Vector2f(4, 4));
	window.draw(info2);
	info2.setColor(sf::Color::White);
	info2.move(sf::Vector2f(-4, -4));
	window.draw(info2);
}

void Gui::drawLevelMenu(sf::RenderWindow &window)
{
	/*ustawienie i narysowanie tla*/
	pauseMenu.setPosition(window.mapPixelToCoords(sf::Vector2i(465, 85)));
	window.draw(pauseMenu);
	/*ustawienie i narysowanie tekstow z opcjami*/
	for (size_t i = 0; i < levelOptions.size(); ++i)
	{
		levelOptions[i].setPosition(window.mapPixelToCoords(sf::Vector2i(480, 60 + static_cast<int>(i) * 45)));
		window.draw(levelOptions[i]);
	}	
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(hpGauge);
	target.draw(expGauge);
	target.draw(skill1);
	target.draw(skill2);
	target.draw(skill3);
}

sf::RectangleShape Gui::getResumeButton()
{
	return resumeButton;
}

sf::RectangleShape Gui::getSaveButton()
{
	return saveButton;
}

sf::RectangleShape Gui::getQuitButton()
{
	return quitButton;
}

void Gui::setResumeHighlight(short swtch)
{
	if (swtch == 0) resumeButton.setTextureRect(sf::IntRect(0, 384, 320, 100)); /*niepodswietlony*/
	else resumeButton.setTextureRect(sf::IntRect(320, 384, 320, 100)); /*podswietlony*/
}

void Gui::setSaveHighlight(short swtch)
{
	if (swtch == 0) saveButton.setTextureRect(sf::IntRect(0, 384, 320, 100)); /*niepodswietlony*/
	else saveButton.setTextureRect(sf::IntRect(320, 384, 320, 100)); /*podswietlony*/
}

void Gui::setQuitHighlight(short swtch)
{
	if (swtch == 0) quitButton.setTextureRect(sf::IntRect(0, 384, 320, 100)); /*niepodswietlony*/
	else quitButton.setTextureRect(sf::IntRect(320, 384, 320, 100)); /*podswietlony*/
}

void Gui::pushDamageInfo(TextDamage* newText)
{
	/*ustawienie tekstu*/
	newText->text.setFont(font);
	newText->text.setCharacterSize(40);
	newText->text.move(-newText->text.getGlobalBounds().width / 2, 0.0);
	/*wystartowanie zegarow*/
	newText->tick.restart();
	newText->lifeTime.restart();
	damageInfo.push_back(newText); /*dodanie do kontenera*/
}

void Gui::pushHpInfo(HpBar* newHpInfo)
{
	hpInfo.push_back(newHpInfo);
}

void Gui::updateHpInfo(size_t i, sf::Vector2f position, short currentHp, short maximumHp)
{
	hpInfo[i]->characterPosition = position; /*przyjecie aktualnej pozycji przeciwnika*/
	/*ustawienie rozmiarow w zaleznosci od stosunku procentowego obecnego hp do maksymalnego*/
	hpInfo[i]->currentHp.setSize(sf::Vector2f((static_cast<float>(currentHp) / static_cast<float>(maximumHp)) * 64.f, 6));
	hpInfo[i]->missingHp.setSize(sf::Vector2f(64.f - (static_cast<float>(currentHp) / static_cast<float>(maximumHp)) * 64.f, 6));
}

void Gui::eraseHpInfo(size_t i)
{
	delete hpInfo[i];
	hpInfo.erase(hpInfo.begin() + i);
}

size_t Gui::getHpInfoSize()
{
	return hpInfo.size();
}

void Gui::clearHpInfo()
{
	hpInfo.clear();
}

void Gui::updateSkillCooldowns(sf::RenderWindow &window, float ratioSkill1, float ratioSkill2, float ratioSkill3)
{
	sf::IntRect temp;
	
	/*przyciecie niezaladowanej czesci umiejetnosci w zaleznosci od uplynietego czasu od uzycia umiejetnosci*/
	fadedSkill1.setSize(sf::Vector2f(64.f, truncf(ratioSkill1 * 64.f)));
	fadedSkill2.setSize(sf::Vector2f(64.f, truncf(ratioSkill2 * 64.f)));
	fadedSkill3.setSize(sf::Vector2f(64.f, truncf(ratioSkill3 * 64.f)));
	temp = fadedSkill1.getTextureRect();
	temp.height = fadedSkill1.getSize().y;
	fadedSkill1.setTextureRect(temp);
	temp = fadedSkill2.getTextureRect();
	temp.height = fadedSkill2.getSize().y;
	fadedSkill2.setTextureRect(temp);
	temp = fadedSkill3.getTextureRect();
	temp.height = fadedSkill3.getSize().y;
	fadedSkill3.setTextureRect(temp);

	fadedSkill1.setPosition(window.mapPixelToCoords(sf::Vector2i(482, 636)));
	fadedSkill2.setPosition(window.mapPixelToCoords(sf::Vector2i(608, 636)));
	fadedSkill3.setPosition(window.mapPixelToCoords(sf::Vector2i(734, 636)));
	skill1.setPosition(window.mapPixelToCoords(sf::Vector2i(482, 636)));
	skill2.setPosition(window.mapPixelToCoords(sf::Vector2i(608, 636)));
	skill3.setPosition(window.mapPixelToCoords(sf::Vector2i(734, 636)));
}