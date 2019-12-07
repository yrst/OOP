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
		int health_max, current_health, strenght, dexterity;
		int current_lvl, current_xp, need_xp;
		bool life;//нужна как условие выхода из боя и  для возможных айтемов, которые избегают смерти, тип хп 0, но лайф остается тру и можно продолжить играть накинув 50 хп и сломав предмет, если он есть (например)
		friend class Fight;
		friend class Inventory;

	public:
		Player(string n){ //создание лоха 1го лвла
			name = n;
			life = true;
			health_max =current_health = rand() % 4 + 8; //start hp [8-12]
			strenght = rand() % 7 + 10; // [start str [10-16]
			dexterity = rand() % 5 + 10; // start dex [10-14]
			current_lvl = 1;
			current_xp = 0;
			need_xp = 300;

			system("clear");
			cout << name << " создан" << endl;
		}

		//формулы для модификаторов от лвл пропишу позже, пока так, условно
		void lvlmodifier (int lev) {
			cout << "После (пока что псевдо) апдейта от лвл" << endl;
			health_max = health_max + lev*8;
			current_health = current_health+ lev*8;
			strenght = strenght + lev;
			dexterity = dexterity + lev;
			cout << "Текущее здоровье " << current_health << " из "<< health_max << endl;
			cout << "Сила " << strenght << endl;
			cout << "Ловкость " << dexterity << endl;
		}

		//функция вывода текущего состояния хар-к персонажа
		void listp (){
			cout << name << endl;
			cout << "Уровень " << current_lvl << endl;
			cout << "Текущее здоровье " << current_health << " из "<< health_max << endl;
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
		int current_health, health_max, strenght, dexterity, lvl;
		int xp_give;
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
				cout << "Текущее здоровье " << current_health << " из "<< health_max << endl;
				cout << "Сила " << strenght << endl;
				cout << "Ловкость " << dexterity << endl;
		  	cout << "----------------"<<endl;
		}
};

class Bandit : public Mob{
	private:

		void mob_init(string n){	//создание бандита
				name = n;
				current_health = health_max = 20;
				strenght = 16;
				dexterity = 10;
				lvl = 5;
				xp_give = 250;
		}

	public:
		Bandit(string n) : Mob(n){
			mob_init(n);
			cout << "'бандит' завершено" << endl;
		}

		virtual void Fight_log(){
 		 cout << "Перед тобой стоит вылитый уголовник с саблей наперевес." << endl << "Настроен он явно агрессивно"<<endl<<"Советую что-то предпринять!"<< endl;
 	 }

};

class Rat:public Mob{
	private:

		  virtual void mob_init(string n){	//создание рики
		 		 name = n;
		 		 current_health = health_max = 6;
		 		 strenght = 2;
		 		 dexterity = 2;
		 		 lvl = 1;
 				 xp_give = 40;
		  }

	public:
		Rat(string n) : Mob(n){
			mob_init(n);
			cout << "'крыса' завершено" << endl;
		}


		virtual void Fight_log(){
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
	 		//system("clear");
			cout<< "Пошла заруба"<< endl;
			enemy_mob.Fight_log(); // С кем встретился
			 Fight_against(character,enemy_mob); //вызов сценария боя, можно потом переделать этот класс на "взаимодействие" и в нём вызывать сценарий боя

		}
		~Fight(){
			cout<< "Бой окончен."<<endl;
		}

	private:

		template < class  mobclass >
		void Fight_against(Player &character, mobclass &enemy_mob){
			int i,comand_cin;
				while((character.life==true) && (enemy_mob.current_health>0)){ //пока жив игрок или моб
					cout << "Что будете делать с "<< enemy_mob.name <<endl;
					cin >> comand_cin;
					if(comand_cin==1){
						attack(character, enemy_mob); // ВЖБАН
					}
					if(comand_cin==4){
						run_away(character, enemy_mob); // По съёбам
					}
				}
				if((enemy_mob.current_health==0)&&(comand_cin!=4)){
					character.current_xp += enemy_mob.xp_give;
					if(character.current_xp>=character.need_xp){
						character.need_xp*=3;
						character.lvlmodifier(1);
					}
				}
				else{
					if(character.current_health==0){
						cout << " You died ¯|_(ツ)_/¯"<<endl;
					}
				}
		}

		template < class  mobclass >
		void attack(Player &character, mobclass &enemy_mob){
			int attack_player_damage;
			attack_player_damage=((character.strenght-10)/2) + rand()%4;
			enemy_mob.current_health=enemy_mob.current_health - attack_player_damage;
			cout << "Oof" << endl << enemy_mob.name << "  получил " << attack_player_damage << " урона." << endl;
			cout << "У " << enemy_mob.name << " осталось всего " << enemy_mob.current_health << " хп" << endl;
		}


		template < class  mobclass >
		void run_away(Player &character, mobclass &enemy_mob){
			int ran_atemp = (rand()%20)+1 + (character.dexterity-10)/2;
			cout << ran_atemp;
			if(ran_atemp>=enemy_mob.dexterity){
				enemy_mob.current_health = 0;
				cout << "При попытке побега от вас и след простыл"<<endl;
			}
			else{
				cout << "Вы попытались убежать, но споткнулись об камень и упали."<< endl << "Коленочке очень больно: -3хп" << endl;
				character.current_health = character.current_health -3;
			}
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
 	//system("clear");

	if(WelcomeScreen()==66){
		cout << " You died ¯|_(ツ)_/¯"<<endl;
		return 0;
	}
	string name;
	cin >> name;
	Player p(name);
	Inventory inven;
	p.listp();
	if(1){
		Bandit gary("Gary");
		gary.listp();
		Fight init(p,gary); //вызвать боёвку с гари
	}
	if(1){
		Rat raticat("Rattat");
		raticat.listp();
		Fight init_rat(p,raticat);
	}

	return 0;
}
