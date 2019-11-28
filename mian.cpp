#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
//#include <locale>

using namespace std;

class Inventory;

class Player {
	private:
		string name;
		int health, strenght, dexterity, lvl;
		bool life;//нужна как условие выхода из боя и  для возможных айтемов, которые избегают смерти, тип хп 0, но лайф остается тру и можно продолжить играть накинув 50 хп и сломав предмет, если он есть (например)

	public:
		friend class Inventory;
		Player(string n){ //создание лоха 1го лвла
			name = n;
			life = true;
			health = rand() % 4 + 8; //start hp [8-12]
			strenght = rand() % 3 + 5; // [start str [5-8]
			dexterity = rand() % 3 + 4; // start dex [4-7]
			lvl = 1;
			system("clear");
			cout << name << " создан" << endl;
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

		//функция вывода текущего состояния хар-к персонажа
		void listp (){
			cout << name << endl;
			cout << "Уровень " << lvl << endl;
			cout << "Здоровье " << health << endl;
			cout << "Сила " << strenght << endl;
			cout << "Ловкость " << dexterity << endl;

		}


};

class Mob{
	protected:
		string name;
		int health, strenght, dexterity, lvl;
		virtual void mob_init(string n){};

	public:

		Mob(string n){
			cout << "#Создание моба категории ";
		} //пока пустышка, тут просто задача тех же параметров что и плеер в зависимости от хар-к плеера (+-2-3 от плееровских)


		void listp (){
			  cout << "----------------"<<endl;
				cout << name << endl;
				cout << "Уровень " << lvl << endl;
				cout << "Здоровье " << health << endl;
				cout << "Сила " << strenght << endl;
				cout << "Ловкость " << dexterity << endl;
		  	cout << "----------------"<<endl;
		}
};

class Bandit : public Mob{
	public:
		Bandit(string n) : Mob(n){
			mob_init(n);
			cout << "'бандит' завершено" << endl;
		}

	protected:
		void mob_init(string n){	//создание бандита
				name = n;
				health = 20;
				strenght = 4;
				dexterity = 4;
				lvl = 10;
		}

};

class Rat:public Mob{
	public:
		Rat(string n) : Mob(n){
			mob_init(n);
			cout << "'крыса' завершено" << endl;
		}

	protected:
	  void mob_init(string n){	//создание рики
	 		 name = n;
	 		 health = 6;
	 		 strenght = 2;
	 		 dexterity = 2;
	 		 lvl = 1;
	  }
};

class Item {
	friend class Player;
	protected:
	int item_str, item_dex, item_health;
	// теперь нужно как-то создать предметы разные, чтоб они существовали (можно как ты сказал подклассы (а-ля абстрактные))
};

class Inventory{
	protected:
		int *item_id_backpack;

	public:
		Inventory(){
			cout<< "#Инициализация инвентаря" << endl;
		}
		~Inventory() {
				cout<< "~Деструкторизация инвентаря" << endl;
			}
};

class Dialoges{

};


int WelcomeScreen(){
	cout << " Wake up, Neo"<<endl;
	cout << " We have the city to burn!"<<endl<< endl<< " Проснуться?"<<endl<< " ";
	string answer;
	cin >> answer;
	if(answer=="Да"){
		return 0;
	}
	return 66;
}

int main() {
	setlocale( LC_ALL,"Russian" ); //русское имя все равно вводить не получается ы
	srand(time(NULL));
 	system("clear");

	if(WelcomeScreen()==66){
		cout << " You died ¯|_(ツ)_/¯"<<endl;
		return 0;
	}
	string name;
	cin >> name;
	Player p(name);
	Inventory inven;
	p.listp();
	p.lvlmodifier(5); //пример работы лвл модифаера

	Bandit gary("Gary");
	gary.listp();

	return 0;
}
