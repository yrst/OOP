#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
//#include <locale>

using namespace std;

class Inventory;
class Fight;

class Player {
	private:
		string name;
		int health, strenght, dexterity, lvl;
		bool life;//нужна как условие выхода из боя и  для возможных айтемов, которые избегают смерти, тип хп 0, но лайф остается тру и можно продолжить играть накинув 50 хп и сломав предмет, если он есть (например)
		friend class Fight;

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
	private:
		friend class Fight;
		friend class Player;
	protected:
		string name;
		int health, strenght, dexterity, lvl,maxhealth;
		virtual void mob_init(string n){};
		virtual void Fight_log(){};

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
		friend class Fight;
		Bandit(string n) : Mob(n){
			mob_init(n);
			cout << "'бандит' завершено" << endl;
		}

	protected:
		void mob_init(string n){	//создание бандита
				name = n;
				health = maxhealth = 20;
				strenght = 4;
				dexterity = 4;
				lvl = 10;
		}

		void Fight_log(){
 		 cout << "Перед тобой стоит вылитый уголовник с саблей наперевес." << endl << "Настроен он явно агрессивно"<<endl<<"Совет что-то предпринять!"<< endl;
 	 }

};

class Rat:public Mob{
	public:
		friend class Fight;
		Rat(string n) : Mob(n){
			mob_init(n);
			cout << "'крыса' завершено" << endl;
		}

	protected:
	  void mob_init(string n){	//создание рики
	 		 name = n;
	 		 health = maxhealth = 6;
	 		 strenght = 2;
	 		 dexterity = 2;
	 		 lvl = 1;
	  }

		void Fight_log(){
 		 cout << "Вы слышите нервирующий писк издаваемый грязным клочком меха." << endl << "Писк ОООоочень противный."<<endl<<"Может прибить, чтобы не мучилась?"<< endl;
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

class Fight{
	public:
		template < class  mobclass >
		Fight(Player &character, mobclass &enemy_mob){
	 		system("clear");
			cout<< "Пошла заруба"<< endl;
			enemy_mob.Fight_log();
			 Fight_against(character,enemy_mob);

		}
		~Fight(){
			cout<< "Бой окончен."<<endl;
		}

	private:

		template < class  mobclass >
		void Fight_against(Player &character, mobclass &enemy_mob){
			int i,comand_cin;
				while((character.life==true) && (enemy_mob.health>0)){ //пока жив игрок или моб
					cout << "Вы атакуете "<< enemy_mob.name <<endl;
					cin >> comand_cin;
					if(comand_cin==1){
						attack(character, enemy_mob);
					}

				}
		}

		template < class  mobclass >
		void attack(Player &character, mobclass &enemy_mob){
			enemy_mob.health=enemy_mob.health - character.strenght;
			cout << "Oof" << endl << enemy_mob.name << "  получил " << character.strenght << " урона." << endl;
			cout << "У " << enemy_mob.name << " осталось всего " << enemy_mob.health << " хп" << endl;
		}

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
	if(1){
		Bandit gary("Gary");
		gary.listp();
		Fight init(p,gary);
	}
	if(1){
		Rat raticat("Rattat");
		raticat.listp();
		Fight init_rat(p,raticat);
	}

	return 0;
}
