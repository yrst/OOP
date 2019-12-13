#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <string>

#include <unistd.h>
//#include <locale>

using namespace std;

class Inventory;
class Fight;
void FurtherDialog();

class Player {
private:
  string name;
  int health_max, health_current, strenght, dexterity;
  int lvl_current, xp_current, xp_need;
  friend class Fight;
  friend class Inventory;
  friend class Entry_level;

public:
  bool
      life; //����� ��� ������� ������ �� ��� �  ��� ��������� �������, �������
            //�������� ������, ��� �� 0, �� ���� �������� ��� � ����� ����������
            //������ ������� 50 �� � ������ �������, ���� �� ���� (��������)

  Player(string n) { //�������� ���� 1�� ����
    name = n;
    life = true;
    health_max = health_current = rand() % 4 + 8; // start hp [8-12]
    strenght = rand() % 7 + 10;                   // [start str [10-16]
    dexterity = rand() % 5 + 10;                  // start dex [10-14]
    lvl_current = 1;
    xp_current = 0;
    xp_need = 300;
    // cout << "DEBUG: " << name << " ������" << endl;
  }

  void lvlmodifier(int lev) {
    cout << "\t\t�����!!!" << endl;
    cout << "��� ���� ����������� �����.";
    health_max = health_max + lev * 8;
    health_current = health_current + lev * 8;
    strenght = strenght + lev;
    dexterity = dexterity + lev;
    cout << "������� �������� " << health_current << " �� " << health_max
         << endl;
    cout << "���� " << strenght << endl;
    cout << "�������� " << dexterity << endl;
  }

  //������� ������ �������� ��������� ���-� ���������
  void listp() {
    cout << "----------------" << endl;
    cout << "��� ���������: " << name << endl;
    cout << "�������: " << lvl_current << endl;
    cout << "������� ��������: " << health_current << " �� " << health_max
         << endl;
    cout << "����: " << strenght << endl;
    cout << "��������: " << dexterity << endl;
    cout << "----------------" << endl;
  }

  static void Player_death_check(Player *&character) {
    if (character->health_current <= 0) {
      character->life = false;
    }
  }
};

class Mob {
private:
  friend class Fight;
  friend class Player;

protected:
  string name;
  int health_current, health_max, strenght, dexterity, lvl_current;
  int xp_give;
  virtual void mob_init(string n){};
  virtual void Fight_log(){};

public:
  Mob(string n) {
    // cout << " DEBUG: c������� ���� ��������� ";
  }

  void listp() {
    cout << "----------------" << endl;
    cout << "���: " << name << endl;
    cout << "�������: " << lvl_current << endl;
    cout << "������� ��������: " << health_current << " �� " << health_max
         << endl;
    cout << "����: " << strenght << endl;
    cout << "��������: " << dexterity << endl;
    cout << "----------------" << endl;
  }
};

class Bandit : public Mob {
private:
  void mob_init(string n) { //�������� �������
    name = n;
    health_current = health_max = 20;
    strenght = 16;
    dexterity = 13;
    lvl_current = 5;
    xp_give = 250;
  }

public:
  Bandit(string n) : Mob(n) {
    mob_init(n);
    // cout << endl << "DEBUG: '������' ���������" << endl;
  }

  virtual void Fight_log() {
    cout << "����� ����� ����� ������� ��������� � ������ ���������." << endl
         << "�������� �� ���� ����������" << endl;
	  sleep(1);
    cout << "������� ���-�� �����������!" << endl;
  }
};

class Rat : public Mob {
private:
  virtual void mob_init(string n) { //�������� ����
    name = n;
    health_current = health_max = 6;
    strenght = 2;
    dexterity = 2;
    lvl_current = 1;
    xp_give = 40;
  }

public:
  Rat(string n) : Mob(n) {
    mob_init(n);
    // cout << endl << "DEBUG: '�����' ���������" << endl;
  }

  virtual void Fight_log() {
    cout << "�� ������� ����������� ���� ���������� ������� ������� ����."
         << endl
         << "���� ��������� ���������." << endl
         << "����� �������, ����� �� ��������?" << endl;
  }
};

class Dummy : public Mob { //�������
private:
  virtual void mob_init(string n) {
    name = n;
    health_current = health_max = 1000;
    strenght = 0;
    dexterity = 0;
    lvl_current = 1000;
    xp_give = 0;
  }

public:
  Dummy(string n) : Mob(n) {
    mob_init(n);
    // cout << endl << "DEBUG: '�����' ���������" << endl;
  }

  virtual void Fight_log() {
    cout << "������� ����� �����, �� ����������.\n"
            "��� ������ ������� ��� �������?\n"
            "�������� - ������� ������� "
         << endl;
  }
};

class Item {
  friend class Player;

protected:
  int item_str, item_dex, item_health;
  // ������ ����� ���-�� ������� �������� ������, ���� ��� ������������ (�����
  // ��� �� ������ ��������� (�-�� �����������))
};

class Inventory {
protected:
  int *item_id_backpack;

public:
  Inventory() {
    // cout << endl << "DEBUG: ������������� ���������" << endl;
  }
  ~Inventory() {
    // cout << endl<< "DEBUG: ���������������� ���������" << endl;
  }
};

class Dialoges {};

class Narrative {
public:
  static void Awaken_Start() {
    sleep(1);
    cout << "������ �����, �� ����������� ������ ������� � ���� ��� \n"
            "������������ �������� ��������� ������, ��� �� �� �����.";
    sleep(2);
    cout << endl
         << "������ �����, ��������� 2 ������ ����� ������������ ��� \n� "
            "������.";
    sleep(2);
    cout << endl
         << endl
         << "����� � ���� � ������ �������� �������, ���������� �����:";
    sleep(1);
    cout << endl << "-��� ���� �����?";
  }
};

class History_procedure {

public:
  void Display_Elipsis() {

    sleep(1);
    cout << ". ";
    sleep(1);
    cout << ". ";
    sleep(1);
    cout << "." << endl;
    sleep(1);
  }

  void Sudden_Death() {
    Display_Elipsis();
    cout << "You died ?|_(?)_/?" << endl;
  }
};

class Entry_level : public History_procedure {

public:
  int Awaken_Start() {
    cout << "Wake up, Neo" << endl;
    sleep(1);
    cout << "We have the city to burn!" << endl;
    sleep(1);
    cout << endl << "����������? (yes/no)" << endl;

    string answer;
    cin >> answer;
    system("cls");
    if (answer == "yes") {
      return 0;
    }
    return 66;
  }

  string Take_players_name() {
    cout << endl << endl << " *� � ������, ��� ���� �����?*" << endl;
    string name;
    getchar();
    getline(cin, name);
    sleep(1);
    system("cls");
    cout << "����� ����������: " << endl;
    sleep(1);
    cout << "-������ " << name
         << ", � ���� ���� � � ������������ ������ �� ����: \n";
    cout << "��������� ��� ���� ���� ������� � � �� � �������. ������ \n"
            "���������, ��� ������ �� ����� �������� ���� �������. ";
    FurtherDialog();
    return name;
  }

  void Stat_Explanation(Player *&character) {
    system("cls");
    cout << "-������ �����-�� ����." << endl;
    sleep(1);
    cout << "��� ���� ��������������:" << endl << endl;
    character->listp();
    sleep(1);
    cout << endl << "� ���� �� �� ����������� �� ����� ������� ����." << endl;
    sleep(1);
    cout << "����������� ����� �� ����������� ��������, �� ��" << endl
         << "�� ������ ��������� ����� ��������� ������, ��-��." << endl;
    FurtherDialog();
  }

  void Fight_Train(Player *&character) {
    system("cls");
    cout << "- ������ ������� � ����� ���������� ����� ������ \n���������� "
            "����� - ���������� ���."
         << endl;
    string answer;
    sleep(1);
    cout << endl << "#�� ������ �������� � ������� ���? (yes/no)" << endl;
    cin >> answer;
    getchar();
		bool train = true;
    if (answer != "yes") { //���� �� ������, ���� �� ��� ������� ���������
      cout << endl << "- ��� " << endl;
      sleep(1);
      cout << "����";
      train =false;
    }
		if(train==true){
	    cout << "- ���, � �� ������, ��� ��������.\n- ����, ����� ��������� ��� �� "
	            "������ "
	         << endl;
	    sleep(1);
	    FurtherDialog();
	    system("cls");
	    cout << "����� ���� ����� ���������� �������.\n�� �������� ���������� "
	            "������, ����� �������� ���.\n��� �� ������ ������� � ���? \n 1-"
	            "���������\t 2-���������� � ���\t 3-�������\t 4-������ �� ������"
	         << endl;

	    int hpm = 0, good_end = 0, just_end = 0, estimate=0, ans = 0;
	    while (train == true) {
	      cin >> ans;
	      system("cls");

	      if (ans == 1) {
					if(hpm<2){
						if(hpm==0){
	        		cout << "�� �������� �������. ��� �������, ��� ��� ������."<<endl;
							sleep(1);
							cout << "�� �������� ��������� ��������."<<endl;
							sleep(1);
							cout << "�� ������� ������� �� ��� � �����." << endl;
						 }
						 else{
						 	if(hpm==1){
						 		cout << "��������� ��������� �������, �� �� ���������� ��"
						 				"\n������ ������."<<endl;
						 		sleep(1);
						 		cout << "������� ��� ���� �� ��������" <<endl;
							 }

						 }
					}
	        hpm++;
	      }
	      if (ans == 2) {
					if(good_end<2){
		        cout << "�� �������� �������� ��������� ������� ����. ��� �������,"
						"\n�� �������, ������� ���� ������ �������� �� ���" << endl;
					}
	        good_end++;
	      }
				if (ans == 3){
					if (estimate ==0){
						cout << endl <<"������� ��� �������, ������ ���������."<<endl;
						estimate++;
					}
					else
						if (estimate == 1){
							cout << endl <<"������� ��� �������, �����-�� ������ ���������."<<endl;
							estimate++;
						}
						else
							if (estimate == 2){
								cout << endl <<"������� ��� �������, ������� ������ ���������."<<endl;
								sleep(1);
								cout << "���� ��������-��" << endl;
								sleep(1);
								cout << "�� ��������� �� ������ � �������� ���� ������� �����������"<<endl;
								estimate++;
							}
							else
								if (estimate ==3){
									cout << endl <<"������� ����������� ������."<<endl;
								}
				}

	      if (ans == 4) {
					if(just_end<2){
		        cout << "�� ������ �� �������. \n��� � ���������, ������� ���� ������ �� ������." << endl;
						Display_Elipsis();
						cout <<endl << "-������� ���� ����� ���� ���-�� �������."<<endl;
					}
	        just_end++;
				}

	      if (hpm ==3) {
	        system("cls");
	        sleep(1);
	        cout << "������� �� ���������� ������ �������������. \n��� �������, "
	                "��� �� ��� ���� �������� ���� ����."
	             << endl;
	        sleep(1);
	        cout << "-��, ��� � ��������� �������."
	             << endl;
	        sleep(1);
	        cout << "-����, ���� �� ����� ���� �� ������ ����, �� �� ���� ����, ������." << endl;
	        sleep(1);
	        train = false;
					getchar();
	      }

	      if (good_end == 3) {
	        system("cls");
	        sleep(1);
	        cout << "��� ����������, ��� ������� ��������� ���. \n���������� "
	                "������� �� ����������� �� ����."
	             << endl;
	        sleep(2);
	        cout << endl
	             << "-���, �������. �� ������������� ����. \n-�������, �� "
	                "���������, ��� ������ ��� ������ ������ ��������."
	             << endl;
	        sleep(2);
	        cout << endl
	             << "-�� ��� ����, � ����, ��� �� ������� ���� �����, ���� "
	                "�����������. \n-����� ���������"
	             << endl;
	        sleep(2);
	        cout << endl
	             << "-�������, � ������� ����. ��� ���� ���� �����.\n-� �� "
	                "������� �� ������ �������� ���� ������� � ��������������.\n- "
	                "��� ����� �������"
	             << endl;
	        sleep(1);
	        character->xp_current += 300;
	        if (character->xp_current >= character->xp_need) {
	          character->xp_need *= 3;
	          character->lvlmodifier(1);
	        }
	        train = false;
					getchar();
	      }
	      if (just_end == 3) {
	        system("cls");
	        sleep(1);
	        cout << "-���." << endl;
	        sleep(1);
	        cout << "-������." << endl;
	        sleep(1);
	        cout << "-����� �������, ��� �� �� �����." << endl;
	        train = false;
					getchar();
	      }
	      if(train==true){
	    		sleep(1);
				cout << endl << "��� ������? \n 1-���������\t 2-���������� � ���\t 3-�������\t 4-������ �� ������" << endl;
		  }  
	    }
	}
		FurtherDialog();
		system("cls");
  }
};


class Fight {
public:
  template <class mobclass> Fight(Player *&character, mobclass *&enemy_mob) {
    // system("cls");
    cout << "����� ������" << endl;
		sleep(1);
    enemy_mob->Fight_log(); // � ��� ����������
    Fight_against(character, enemy_mob); //����� �������� ���, ����� ����� ���������� ���� �����
                    										 //�� "��������������" � � �� �������� �������� ���
  }
  ~Fight() { cout << "��� �������." << endl; }

private:
  template <class mobclass>
  void Fight_against(Player *&character, mobclass *&enemy_mob) {
    int i, comand_cin;
    while ((character->life == true) && (enemy_mob->health_current > 0)) { //���� ��� ����� ��� ���
      cout << "��� ������ ������ � " << enemy_mob->name << endl
           << "1-���������\t 3-�������\t 4-���������� �������"
           << endl;
      cin >> comand_cin;
      if (comand_cin == 1) {
        attack(character, enemy_mob); // �����
      }
      if (comand_cin == 3) {
        Fight_stat_info(character, enemy_mob); // ���������� ����������
      }
      if (comand_cin == 4) {
        run_away(character, enemy_mob); // �� ������
      }
      character->Player_death_check(character);
      sleep(3);
   	  system("cls");
    }
    if ((enemy_mob->health_current <= 0) && (comand_cin != 4)) {
      character->xp_current += enemy_mob->xp_give;
      if (character->xp_current >= character->xp_need) {
        character->xp_need *= 3;
        character->lvlmodifier(1);
      }
    }
  }

  template <class mobclass>
  void attack(Player *&character, mobclass *&enemy_mob) {
    int attack_player_damage;
    int reverse_attack;
    attack_player_damage = ((character->strenght - 10) / 2) + rand() % 4;
    enemy_mob->health_current =
        enemy_mob->health_current - attack_player_damage;
    cout << "----------------" << endl;
    cout << "Oof" << endl
         << enemy_mob->name << "  ������� " << attack_player_damage << " �����."
         << endl;
    cout << "� " << enemy_mob->name << " �������� ����� "
         << enemy_mob->health_current << " ��" << endl;
    cout << "----------------" << endl;
    sleep(1);
    reverse_attack = rand() % 100;
    if (reverse_attack > 50 && enemy_mob->health_current>0) {
      cout << enemy_mob->name << " ����� ���������!" << endl;
      int reverse_damage;
      cout << "----------------" << endl;
      reverse_damage = (enemy_mob->strenght / 2 + rand() % 3);
      character->health_current = character->health_current - reverse_damage;
      cout << enemy_mob->name << " ������ � ����� � �� �������� "
           << reverse_damage << " �����." << endl;
      if (character->health_current < 0) {
        cout << "� ��� �������� 0 ��" << endl;
      } else
        cout << "� ��� �������� " << character->health_current << " ��" << endl;
      cout << "----------------" << endl;
    }
  }

  template <class mobclass>
  static  void Fight_stat_info(Player *&character, mobclass *&enemy_mob) {
    cout << "----------------" << endl;
    cout << "\t\t" << character->name << "\t\t" << enemy_mob->name << endl;
    cout << "�������          " << character->lvl_current << "\t\t"
         << enemy_mob->lvl_current << endl;
    cout << "������� �������� " << character->health_current << "\t\t"
         << enemy_mob->health_current << endl;
    cout << "����             " << character->strenght << "\t\t"
         << enemy_mob->strenght << endl;
    cout << "��������         " << character->dexterity << "\t\t"
         << enemy_mob->dexterity << endl;
    cout << "----------------" << endl;
  }

  template <class mobclass>
  void run_away(Player *&character, mobclass *&enemy_mob) {
    int ran_atemp = (rand() % 20) + 1 + (character->dexterity - 10) / 2;
    if (ran_atemp >= enemy_mob->dexterity) {
      enemy_mob->health_current = 0;
      cout << "��� ������� ������ �� ��� � ���� �������" << endl;
    } else {
      cout << "�� ���������� �������" << endl;
      sleep(1);
      cout << "�� ����������� �� ������ � �����." << endl;
      sleep(1);
      cout << "��������� ����� ������: -3��" << endl;
      character->health_current = character->health_current - 3;
    }
  }
};

void FurtherDialog() { //��� ����� ����������� ����, ����� ���� ������� ���
                       //����� ��������
  sleep(1);
  cout << endl << endl << "\t\t\t\t '������� Enter, ��� �����������'";
  int input = getchar();
  while (input != 10) {
    input = getchar();
  }
  return;
}


class Level_Forest : public History_procedure{

	public:

		void Adventure_Start(Player *&character){
			system("cls");
			cout << endl
					 << "׸���� ������ ������ ��� �������� ������������."<<endl;
			sleep(1);
			cout << "����� ��������� ����� �� ����������� ���� �������������� � �����-�� ����." <<endl;
			sleep(1);
			cout << "�� ����� � ��� �� ��� ��������������� ���������, �� �� ������ �������� �������." << endl;
			FurtherDialog();
					   Bandit *gary = new Bandit("Gary");
				     system("cls");
				     Fight init_bandit(character, gary); //������� ����� � ����
				     if (character->life == false) {
				       cout << " You died ?|_(?)_/?" << endl;
				       return ;
				     }
		}
};

int main() {
  setlocale(LC_ALL, "Russian");
  srand(time(NULL));
  // system("cls");
  bool fight = false;

  Narrative *narrative = new Narrative();
  Entry_level *entry = new Entry_level();
  if (entry->Awaken_Start() == 66) {
    cout << "�� �� ������ �������, �� ����������� ������ � ��������� "
            "�������."
         << endl;
    sleep(1);
    cout << "����������� � ��������� ����� �� ������ ������ �� �����������."
         << endl;
    entry->Sudden_Death();
    return 0;
  }

  narrative->Awaken_Start();
  string name = entry->Take_players_name();
  Player *p = new Player(name);
  entry->Stat_Explanation(p);
  entry->Fight_Train(p);
	free(entry);

	Level_Forest *adventure = new Level_Forest;
	adventure->Adventure_Start(p);

	if (p->life == true) {
		Rat *raticat = new Rat("Rattat");
		raticat->listp();
		Fight init_rat(p, raticat);
		if (p->life == false) {
			cout << " You died ?|_(?)_/?" << endl;
			return 0;
		}
	}

  return 0;
}

