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
		bool life;//����� ��� ������� ������ �� ��� �  ��� ��������� �������, ������� �������� ������, ��� �� 0, �� ���� �������� ��� � ����� ���������� ������ ������� 50 �� � ������ �������, ���� �� ���� (��������)
	
	Player(string n, int hp, int str, int dex, int lev){
		name = n;
		life = true;
		health = hp; //start hp [8-12]
		strenght = str; // [start str [5-8]
		dexterity = dex; // start dex [4-7]
		lvl = lev;
	}
	
	//������� ��� ������������� �� ��� ������� �����, ���� ���, �������
	void lvlmodifier (int lev) { 
		cout << "����� (���� ��� ������) ������� �� ���" << endl;
		lev = lev / 2;
		health = health + lev;
		strenght = strenght + lev;
		dexterity = dexterity + lev;
		cout << "�������� " << health << endl;
		cout << "���� " << strenght << endl;
		cout << "�������� " << dexterity << endl;
	}
	
		
};

class Mob:public Player {
	public:
	
	Mob(); //���� ��������, ��� ������ ������ ��� �� ���������� ��� � ����� � ����������� �� ���-� ������ (+-2-3 �� �����������)
};

class Item {
	friend class Player;
	protected:
	int item_str, item_dex, item_health;
	// ������ ����� ���-�� ������� �������� ������, ���� ��� ������������ (����� ��� �� ������ ��������� (�-�� �����������))	
};



//������� ������ �������� ��������� ���-� ��������� 
void listp (string n, int health, int strenght, int dexterity, int lvl){
	cout << n << endl;
	cout << "������� " << lvl << endl;
	cout << "�������� " << health << endl;
	cout << "���� " << strenght << endl;
	cout << "�������� " << dexterity << endl;
	
}

int main() {
	setlocale( LC_ALL,"Russian" ); //������� ��� ��� ����� ������� �� ���������� �
	int hlt,str,dex;
	srand(time(NULL));
	hlt = rand() % 4 + 8;
	str = rand() % 3 + 5;
	dex = rand() % 3 + 4;
	string name;
	
	cin >> name;
	Player p(name, hlt, str, dex, 1);
	listp(p.name, p.health, p.strenght, p.dexterity, p.lvl);
	p.lvlmodifier(5); //������ ������ ��� ���������
	return 0;
}
