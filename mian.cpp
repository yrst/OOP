#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//#include <locale>

using namespace std;

class Player {
	public:
		string name;
		int health, strenght, dexterity, lvl;
		bool life;//нужна как условие выхода из боя и  для возможных айтемов, которые избегают смерти, тип хп 0, но лайф остается тру и можно продолжить играть накинув 50 хп и сломав предмет, если он есть (например)

	Player(string n, int hp, int str, int dex, int lev){
		name = n;
		life = true;
		health = hp; //start hp [8-12]
		strenght = str; // [start str [5-8]
		dexterity = dex; // start dex [4-7]
		lvl = lev;
	}

	//формулы для модификаторов от лвл пропишу позже, пока так, условно
	void lvlmodifier (int lev) {
		cout << "После (пока что псевдо) апдейта от лвл" << endl;
		lev = lev / 2;
		health = health + lev;
		strenght = strenght + lev;
		dexterity = dexterity + lev;
		cout << "Здоровье " << health << endl;
		cout << "Сила " << strenght << endl;
		cout << "Ловкость " << dexterity << endl;
	}


};

class Mob:public Player {
	public:

	Mob(); //пока пустышка, тут просто задача тех же параметров что и плеер в зависимости от хар-к плеера (+-2-3 от плееровских)
};

class Item {
	friend class Player;
	protected:
	int item_str, item_dex, item_health;
	// теперь нужно как-то создать предметы разные, чтоб они существовали (можно как ты сказал подклассы (а-ля абстрактные))
};



//функция вывода текущего состояния хар-к персонажа
void listp (string n, int health, int strenght, int dexterity, int lvl){
	cout << n << endl;
	cout << "Уровень " << lvl << endl;
	cout << "Здоровье " << health << endl;
	cout << "Сила " << strenght << endl;
	cout << "Ловкость " << dexterity << endl;

}

int main() {
	setlocale( LC_ALL,"Russian" ); //русское имя все равно вводить не получается ы
	int hlt,str,dex;
	srand(time(NULL));
	hlt = rand() % 4 + 8;
	str = rand() % 3 + 5;
	dex = rand() % 3 + 4;
	string name;

	cin >> name;
	Player p(name, hlt, str, dex, 1);
	listp(p.name, p.health, p.strenght, p.dexterity, p.lvl);
	p.lvlmodifier(5); //пример работы лвл модифаера
	return 0;
}
