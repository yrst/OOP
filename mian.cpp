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

class Player {
private:
  string name;
  int health_max, health_current, strenght, dexterity;
  int lvl_current, xp_current, xp_need;
  friend class Fight;
  friend class Inventory;

public:
  bool
      life; //нужна как условие выхода из боя и  для возможных айтемов, которые
            //избегают смерти, тип хп 0, но лайф остается тру и можно продолжить
            //играть накинув 50 хп и сломав предмет, если он есть (например)

  Player(string n) { //создание лоха 1го лвла
    name = n;
    life = true;
    health_max = health_current = rand() % 4 + 8; // start hp [8-12]
    strenght = rand() % 7 + 10;                   // [start str [10-16]
    dexterity = rand() % 5 + 10;                  // start dex [10-14]
    lvl_current = 1;
    xp_current = 0;
    xp_need = 300;
    system("cls");
    cout << name << " создан" << endl;
  }

  //формулы для модификаторов от лвл пропишу позже, пока так, условно
  void lvlmodifier(int lev) {
    cout << "После (пока что псевдо) апдейта от лвл" << endl;
    health_max = health_max + lev * 8;
    health_current = health_current + lev * 8;
    strenght = strenght + lev;
    dexterity = dexterity + lev;
    cout << "Текущее здоровье " << health_current << " из " << health_max
         << endl;
    cout << "Сила " << strenght << endl;
    cout << "Ловкость " << dexterity << endl;
  }

  //функция вывода текущего состояния хар-к персонажа
  void listp() {
    cout << name << endl;
    cout << "Уровень " << lvl_current << endl;
    cout << "Текущее здоровье " << health_current << " из " << health_max
         << endl;
    cout << "Сила " << strenght << endl;
    cout << "Ловкость " << dexterity << endl;
  }

  void Player_death_check(Player *&character) {
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
    cout << "#Создание моба категории ";
  } //пока пустышка, тут просто задача тех же параметров что и плеер в
    //зависимости от хар-к плеера (+-2-3 от плееровских)

  void listp() {
    cout << "----------------" << endl;
    cout << name << endl;
    cout << "Уровень " << lvl_current << endl;
    cout << "Текущее здоровье " << health_current << " из " << health_max
         << endl;
    cout << "Сила " << strenght << endl;
    cout << "Ловкость " << dexterity << endl;
    cout << "----------------" << endl;
  }
};

class Bandit : public Mob {
private:
  void mob_init(string n) { //создание бандита
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
    cout << "'бандит' завершено" << endl;
  }

  virtual void Fight_log() {
    cout << "Перед тобой стоит вылитый уголовник с саблей наперевес." << endl
         << "Настроен он явно агрессивно" << endl
         << "Советую что-то предпринять!" << endl;
  }
};

class Rat : public Mob {
private:
  virtual void mob_init(string n) { //создание рики
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
    cout << "'крыса' завершено" << endl;
  }

  virtual void Fight_log() {
    cout << "Вы слышите нервирующий писк издаваемый грязным клочком меха."
         << endl
         << "Писк ОООоочень противный." << endl
         << "Может прибить, чтобы не мучилась?" << endl;
  }
};

class Item {
  friend class Player;

protected:
  int item_str, item_dex, item_health;
  // теперь нужно как-то создать предметы разные, чтоб они существовали (можно
  // как ты сказал подклассы (а-ля абстрактные))
};

class Inventory {
protected:
  int *item_id_backpack;

public:
  Inventory() { cout << "#Инициализация инвентаря" << endl; }
  ~Inventory() { cout << "~Деструкторизация инвентаря" << endl; }
};

class Dialoges {};

class Narrative {
public:
  void Awaken_Start() {
    sleep(1);
    cout << endl
         << "Открыв глаза, ты продолжаешь видеть темноту и лишь твоё \n"
            "отрисованное туловище позволяет понять, что ты не ослеп.";
    sleep(1);
    cout << endl
         << "Голова болит, последние 2 минуты твоих воспоминаний как \nв "
            "тумане.";
    sleep(2);
    cout << endl
         << endl
         << "Вдруг у тебя в голове раздаётся хриплый, грубоватый голос:";
    sleep(1);
    cout << endl << "-Как тебя зовут?";
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
    cout << "You died ¯|_(ツ)_/¯" << endl;
  }
};

class Entry_level : public History_procedure {

public:
  int Awaken_Start() {
    cout << "Wake up, Neo" << endl;
    sleep(1);
    cout << "We have the city to burn!" << endl;
    sleep(1);
    cout << endl << "Проснуться? (yes/no)" << endl;

    string answer;
    cin >> answer;
    if (answer == "yes") {
      return 0;
    }
    return 66;
  }

  string Take_players_name() {
    cout << endl << endl << "*И в правду, как меня зовут?*" << endl;
    string name;
    cin >> name;
    sleep(1);
    cout
        << "Кароче " << name
        << ", я тебя спас и в благородство играть не буду: выполнишь для\n"
           "меня пару заданий — и мы в расчете. Заодно посмотрим, как быстро \n"
           "ты после обучения игру пройдёшь. "
        << endl;
    sleep(1);
    return name;
  }
};

class Fight {
public:
  template <class mobclass> Fight(Player *&character, mobclass *&enemy_mob) {
    // system("clear");
    cout << "Пошла заруба" << endl;
    enemy_mob->Fight_log(); // С кем встретился
    Fight_against(
        character,
        enemy_mob); //вызов сценария боя, можно потом переделать этот класс на
                    //"взаимодействие" и в нём вызывать сценарий боя
  }
  ~Fight() { cout << "Бой окончен." << endl; }

private:
  template <class mobclass>
  void Fight_against(Player *&character, mobclass *&enemy_mob) {
    int i, comand_cin;
    while ((character->life == true) &&
           (enemy_mob->health_current > 0)) { //пока жив игрок или моб
      cout << "Что будете делать с " << enemy_mob->name << endl
           << "1 - атаковать, 2 - Оценить противника, 4 - попытаться сбежать"
           << endl;
      cin >> comand_cin;
      if (comand_cin == 1) {
        attack(character, enemy_mob); // ВЖБАН
      }
      if (comand_cin == 2) {
        Fight_stat_info(character, enemy_mob); // Запрашиваю информацию
      }
      if (comand_cin == 4) {
        run_away(character, enemy_mob); // По съёбам
      }
      character->Player_death_check(character);
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
         << enemy_mob->name << "  получил " << attack_player_damage << " урона."
         << endl;
    cout << "У " << enemy_mob->name << " осталось всего "
         << enemy_mob->health_current << " хп" << endl;
    cout << "----------------" << endl;
    sleep(1);
    reverse_attack = rand() % 100;
    if (reverse_attack > 50) {
      cout << enemy_mob->name << " будет атаковать!" << endl;
      int reverse_damage;
      cout << "----------------" << endl;
      reverse_damage = (enemy_mob->strenght / 2 + rand() % 3);
      character->health_current = character->health_current - reverse_damage;
      cout << enemy_mob->name << " ударил в ответ и вы получили "
           << reverse_damage << " урона." << endl;
      if (character->health_current < 0) {
        cout << "У вас осталось 0 хп" << endl;
      } else
        cout << "У вас осталось " << character->health_current << " хп" << endl;
      cout << "----------------" << endl;
    }
  }

  template <class mobclass>
  void Fight_stat_info(Player *&character, mobclass *&enemy_mob) {
    cout << "----------------" << endl;
    cout << "\t\t" << character->name << "\t\t" << enemy_mob->name << endl;
    cout << "Уровень          " << character->lvl_current << "\t\t"
         << enemy_mob->lvl_current << endl;
    cout << "Текущее здоровье " << character->health_current << "\t\t"
         << enemy_mob->health_current << endl;
    cout << "Сила             " << character->strenght << "\t\t"
         << enemy_mob->strenght << endl;
    cout << "Ловкость         " << character->dexterity << "\t\t"
         << enemy_mob->dexterity << endl;
    cout << "----------------" << endl;
  }

  template <class mobclass>
  void run_away(Player *&character, mobclass *&enemy_mob) {
    int ran_atemp = (rand() % 20) + 1 + (character->dexterity - 10) / 2;
    cout << ran_atemp;
    if (ran_atemp >= enemy_mob->dexterity) {
      enemy_mob->health_current = 0;
      cout << "При попытке побега от вас и след простыл" << endl;
    } else {
      cout << "Вы попытались убежать" << endl;
      sleep(1);
      cout << "Но споткнулись об камень и упали." << endl;
      sleep(1);
      cout << "Коленочке очень больно: -3хп" << endl;
      character->health_current = character->health_current - 3;
    }
  }
};

int main() {
  setlocale(LC_ALL, "Russian");
  srand(time(NULL));
  // system("clear");
  bool fight = false;

  Narrative *narrative = new Narrative();
  Entry_level *entry = new Entry_level();
  if (entry->Awaken_Start() == 66) {
    cout << "Вы не можете заснуть, но продолжаете лежать с закрытыми глазами."
         << endl;
    sleep(1);
    cout << "Задумавшись о бренности бытия вы решили больше не просыпаться."
         << endl;
    entry->Sudden_Death();
    return 0;
  }

  narrative->Awaken_Start();
  string name = entry->Take_players_name();
  cout << "Вот твои характеристики" << endl;
  Player *p = new Player(name);
  p->listp();

  string answer;
  cout << "Вы хотите вступить в пробный бой? (yes/no)" << endl;
  cin >> answer;
  system("cls");
  if (answer == "yes") {
    fight = true;
  }
  if (fight == true) {
    Bandit *gary = new Bandit("Gary");
    cout << "Ваш противник" << endl;
    gary->listp();
    sleep(5);
    system("cls");
    Fight init(p, gary); //вызвать боёвку с гари
    if (p->life == false) {
      cout << " You died ¯|_(ツ)_/¯" << endl;
      return 0;
    }
  }
  if (fight == true) {
    Rat *raticat = new Rat("Rattat");
    raticat->listp();
    Fight init_rat(p, raticat);
    if (p->life == false) {
      cout << " You died ¯|_(ツ)_/¯" << endl;
      return 0;
    }
  }

  return 0;
}
