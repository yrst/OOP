#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>

#include <unistd.h>
//#include <locale>

using namespace std;

class Inventory;
class Fight;

class Player {
	private:
		string name;
		int health_max, current_health, strenght, dexterity;
		int current_lvl, current_xp, need_xp;
		bool life;//����� ��� ������� ������ �� ��� �  ��� ��������� �������, ������� �������� ������, ��� �� 0, �� ���� �������� ��� � ����� ���������� ������ ������� 50 �� � ������ �������, ���� �� ���� (��������)
		friend class Fight;
		friend class Inventory;

	public:
		Player(string n){ //�������� ���� 1�� ����
			name = n;
			life = true;
			health_max =current_health = rand() % 4 + 8; //start hp [8-12]
			strenght = rand() % 7 + 10; // [start str [10-16]
			dexterity = rand() % 5 + 10; // start dex [10-14]
			current_lvl = 1;
			current_xp = 0;
			need_xp = 300;

			system("cls");
			cout << name << " ������" << endl;
		}

		//������� ��� ������������� �� ��� ������� �����, ���� ���, �������
		void lvlmodifier (int lev) {
			cout << "����� (���� ��� ������) ������� �� ���" << endl;
			health_max = health_max + lev*8;
			current_health = current_health+ lev*8;
			strenght = strenght + lev;
			dexterity = dexterity + lev;
			cout << "������� �������� " << current_health << " �� "<< health_max << endl;
			cout << "���� " << strenght << endl;
			cout << "�������� " << dexterity << endl;
		}

		//������� ������ �������� ��������� ���-� ���������
		void listp (){
			cout << name << endl;
			cout << "������� " << current_lvl << endl;
			cout << "������� �������� " << current_health << " �� "<< health_max << endl;
			cout << "���� " << strenght << endl;
			cout << "�������� " << dexterity << endl;

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
			cout << "#�������� ���� ��������� ";
		} //���� ��������, ��� ������ ������ ��� �� ���������� ��� � ����� � ����������� �� ���-� ������ (+-2-3 �� �����������)


		void listp (){
			  cout << "----------------"<<endl;
				cout << name << endl;
				cout << "������� " << lvl << endl;
				cout << "������� �������� " << current_health << " �� "<< health_max << endl;
				cout << "���� " << strenght << endl;
				cout << "�������� " << dexterity << endl;
		  	cout << "----------------"<<endl;
		}
};

class Bandit : public Mob{
	private:

		void mob_init(string n){	//�������� �������
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
			cout << "'������' ���������" << endl;
		}

		virtual void Fight_log(){
 		 cout << "����� ����� ����� ������� ��������� � ������ ���������." << endl << "�������� �� ���� ����������"<<endl<<"������� ���-�� �����������!"<< endl;
 	 }

};

class Rat:public Mob{
	private:

		  virtual void mob_init(string n){	//�������� ����
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
			cout << "'�����' ���������" << endl;
		}


		virtual void Fight_log(){
 		 cout << "�� ������� ����������� ���� ���������� ������� ������� ����." << endl << "���� ��������� ���������."<<endl<<"����� �������, ����� �� ��������?"<< endl;
 	 }
};

class Item {
	friend class Player;
	protected:
	int item_str, item_dex, item_health;
	// ������ ����� ���-�� ������� �������� ������, ���� ��� ������������ (����� ��� �� ������ ��������� (�-�� �����������))
};

class Inventory{
	protected:
		int *item_id_backpack;

	public:
		Inventory(){
			cout<< "#������������� ���������" << endl;
		}
		~Inventory() {
				cout<< "~���������������� ���������" << endl;
			}
};

class Dialoges{

};

class Fight{
	public:
		template < class  mobclass >
		Fight(Player &character, mobclass &enemy_mob){
	 		//system("clear");
			cout<< "����� ������"<< endl;
			enemy_mob.Fight_log(); // � ��� ����������
			 Fight_against(character,enemy_mob); //����� �������� ���, ����� ����� ���������� ���� ����� �� "��������������" � � �� �������� �������� ���

		}
		~Fight(){
			cout<< "��� �������."<<endl;
		}

	private:

		template < class  mobclass >
		void Fight_against(Player &character, mobclass &enemy_mob){
			int i,comand_cin;
				while((character.life==true) && (enemy_mob.current_health>0)){ //���� ��� ����� ��� ���
					cout << "��� ������ ������ � "<< enemy_mob.name << endl << "1 - ���������, 2 - ��������������, 4 - ���������� �������" <<endl;
					cin >> comand_cin;
					if(comand_cin==1){
						attack(character, enemy_mob); // �����
					}
					if(comand_cin==4){
						run_away(character, enemy_mob); // �� ������
					}
					if(comand_cin==2){
					  cout << "----------------"<<endl;
						cout << "\t\t" << character.name << "\t\t" << enemy_mob.name << endl;
						cout << "�������          " << character.current_lvl << "\t\t" << enemy_mob.lvl <<endl;
						cout << "������� �������� " << character.current_health << "\t\t" << enemy_mob.current_health << endl;
						cout << "����             " << character.strenght << "\t\t" << enemy_mob.strenght << endl;
						cout << "��������         " << character.dexterity << "\t\t" << enemy_mob.dexterity << endl;
		  				cout << "----------------"<<endl;
					}
				}
				if((enemy_mob.current_health==0)&&(comand_cin!=4)){
					character.current_xp += enemy_mob.xp_give;
					if(character.current_xp>=character.need_xp){
						character.need_xp*=3;
						character.lvlmodifier(1);
					}
				}
				/*if(character.current_health<0){
						cout << " You died ?|_(?)_/?"<<endl;
				}*/
		}

		template < class  mobclass >
		void attack(Player &character, mobclass &enemy_mob){
			int attack_player_damage;
			int reverse_attack;
			attack_player_damage=((character.strenght-10)/2) + rand()%4;
			enemy_mob.current_health=enemy_mob.current_health - attack_player_damage;
			cout << "----------------"<<endl;
			cout << "Oof" << endl << enemy_mob.name << "  ������� " << attack_player_damage << " �����." << endl;
			cout << "� " << enemy_mob.name << " �������� ����� " << enemy_mob.current_health << " ��" << endl;
			cout << "----------------"<<endl;
			sleep(1);
			reverse_attack = rand()%100;
			if (reverse_attack > 50){
				cout << enemy_mob.name << " ����� ���������!" << endl;
				int reverse_damage;
				cout << "----------------"<<endl;
				reverse_damage=(enemy_mob.strenght/2 + rand()%3);
				character.current_health = character.current_health - reverse_damage;
				cout << enemy_mob.name << " ������ � ����� � �� �������� " << reverse_damage << " �����." << endl;
				cout << "� ��� �������� " << character.current_health << " ��" << endl;
				cout << "----------------"<<endl;
			}
			if (character.current_health<=0){
				character.life=false;
					cout << " You died ?|_(?)_/?"<<endl;
					system("cls");
			}
		}


		template < class  mobclass >
		void run_away(Player &character, mobclass &enemy_mob){
			int ran_atemp = (rand()%20)+1 + (character.dexterity-10)/2;
			cout << ran_atemp;
			if(ran_atemp>=enemy_mob.dexterity){
				enemy_mob.current_health = 0;
				cout << "��� ������� ������ �� ��� � ���� �������"<<endl;
			}
			else{
				cout << "�� ���������� �������, �� ����������� �� ������ � �����."<< endl << "��������� ����� ������: -3��" << endl;
				character.current_health = character.current_health -3;
			}
		}

};

int WelcomeScreen(){
	cout << "Wake up, Neo"<<endl;
	sleep(1);
	cout << "We have the city to burn!"<<endl; 
	sleep(1); 
	 cout << endl<< "����������? (yes/no)"<<endl;
	
	string answer;
	cin >> answer;
	if(answer=="yes"){
		return 0;
	}
	return 66;
}

int main() {
	setlocale( LC_ALL,"Russian" ); //������� ��� ��� ����� ������� �� ���������� �
	srand(time(NULL));
 	//system("clear");
	bool fight = false;
	
	
	if(WelcomeScreen()==66){
		cout << "You died ?|_(?)_/?"<<endl;
		return 0;
	}
	cout << "��� ��� �����?" << endl;
	string name;
	cin >> name;
	sleep(1);
	cout << "����� �������, " << name << endl;
	sleep(1);
	cout << "��� ���� ��������������" << endl;
	sleep(2);
	Player p(name);
	
	Inventory inven;
	p.listp();
	string answer;
	cout << "�� ������ �������� � ������� ���? (yes/no)" << endl;
	cin >> answer;
	system("cls");
	if(answer=="yes"){
		fight = true;
	}
	if(fight == true){
		Bandit gary("Gary");
		cout << "��� ���������" << endl;
		gary.listp();
		sleep(5);
		system("cls");
		Fight init(p,gary); //������� ����� � ����
	}
	if(fight == true){
		Rat raticat("Rattat");
		raticat.listp();
		Fight init_rat(p,raticat);
	}

	return 0;
}

