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
    // cout << "DEBUG: " << name << " создан" << endl;
  }

  void lvlmodifier(int lev) {
    cout << "\t\tДЗЫНЬ!!!" << endl;
    cout << "Твоё тело наполняется силой.";
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
    cout << "----------------" << endl;
    cout << "Имя персонажа: " << name << endl;
    cout << "Уровень: " << lvl_current << endl;
    cout << "Текущее здоровье: " << health_current << " из " << health_max
         << endl;
    cout << "Сила: " << strenght << endl;
    cout << "Ловкость: " << dexterity << endl;
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
    // cout << " DEBUG: cоздание моба категории ";
  }

  void listp() {
    cout << "----------------" << endl;
    cout << "Имя: " << name << endl;
    cout << "Уровень: " << lvl_current << endl;
    cout << "Текущее здоровье: " << health_current << " из " << health_max
         << endl;
    cout << "Сила: " << strenght << endl;
    cout << "Ловкость: " << dexterity << endl;
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
    // cout << endl << "DEBUG: 'бандит' завершено" << endl;
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
    // cout << endl << "DEBUG: 'крыса' завершено" << endl;
  }

  virtual void Fight_log() {
    cout << "Вы слышите нервирующий писк издаваемый грязным клочком меха."
         << endl
         << "Писк ОООоочень противный." << endl
         << "Может прибить, чтобы не мучилась?" << endl;
  }
};

class Dummy : public Mob { //МАНЕКЕН
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
    // cout << endl << "DEBUG: 'крыса' завершено" << endl;
  }

  virtual void Fight_log() {
    cout << "Манекен стоит гордо, но беспомощно.\n"
            "Кто вообще захочет его ударить?\n"
            "Очевидно - ужасный человек "
         << endl;
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
  Inventory() {
    // cout << endl << "DEBUG: Инициализация инвентаря" << endl;
  }
  ~Inventory() {
    // cout << endl<< "DEBUG: Деструкторизация инвентаря" << endl;
  }
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
    system("clear");
    if (answer == "yes") {
      return 0;
    }
    return 66;
  }

  string Take_players_name() {
    cout << endl << endl << " *И в правду, как меня зовут?*" << endl;
    string name;
    getchar();
    getline(cin, name);
    sleep(1);
    system("clear");
    cout << "Голос продолжает: " << endl;
    sleep(1);
    cout << "- Кароче " << name
         << ", я тебя спас и в благородство играть не буду: \n";
    cout << "выполнишь для меня пару заданий — и мы в расчете. Заодно \n"
            "посмотрим, как быстро ты после обучения игру пройдёшь. ";
    FurtherDialog();
    return name;
  }

  void Stat_Explanation(Player *&character) {
    system("clear");
    cout << endl << "- Теперь глянь-ка сюда." << endl;
    sleep(1);
    cout << "Вот твои характеристики:" << endl << endl;
    character->listp();
    sleep(1);
    cout << endl << "С ними ты не растанешься до конца свовего пути." << endl;
    sleep(1);
    cout << "Обязательно следи за показателем здоровья, ты же" << endl
         << "не хочешь неожидано стать очередным жмуром, хе-хе." << endl;
    FurtherDialog();
  }

  void Fight_Train(Player *&character) {
    system("clear");
    cout << "- Теперь перейдём к более интересной части твоего \nпребывания "
            "здесь - тренировке боя."
         << endl;
    string answer;
    sleep(1);
    cout << endl << "#Вы хотите вступить в пробный бой? (yes/no)" << endl;
    cin >> answer;
    getchar();
    if (answer != "yes") { //выхд из метода, если не хош бучение проходить
      cout << endl << "- МММ " << endl;
      sleep(1);
      cout << "Ясно";
      FurtherDialog();
      return;
    }
    cout << "- Хах, а ты смелее, чем кажешься.\n- Чтож, давай посмотрим что ты "
            "можешь "
         << endl;
    sleep(1);
    FurtherDialog();
    system("clear");
    cout << endl
         << "Перед вами вдруг появляется манекен.\n Он выглядит достаточно "
            "грзно, чтобы напугать вас.\n Что вы хотите сделать с ним? \n 1 - "
            "атаковать 2 - поговорить с ним 3 - убежать"
         << endl;

    bool train = true;
    int hpm = 4, good_end = 0, bad_end = 0, ans = 0;
    while (train == true) {
      cin >> ans;
      system("clear");
      if (ans == 1) {
        cout << endl
             << "Вы атакуете манекен. Вам кажется, что это нелепо.\n На "
                "манекене появилась царапина.\n Он жалобно смотрит на вас в "
                "ответ."
             << endl;
        hpm--;
        sleep(1);
        cout << "Что дальше? \n 1 - атаковать 2 - поговорить с ним 3 - убежеать"
             << endl;
      }

      if (ans == 2) {
        cout << endl
             << "Вы говорите манекену несколько хороших слов. \n Вам кажется, "
                "что манекен стал добрее смотреть на вас"
             << endl;
        good_end++;
        sleep(1);
        cout << "Что дальше? \n 1 - атаковать 2 - поговорить с ним 3 - убежеать"
             << endl;
      }

      if (ans == 3) {
        cout << "Вы попытались убежать. Вы переоценили себя. \n Неизвестная "
                "сила вернула вас назад."
             << endl;
        bad_end++;
        sleep(1);
        cout << "Что дальше? \n 1 - атаковать 2 - поговорить с ним 3 - убежеать"
             << endl;
      }

      if (hpm == 0) {
        system("clear");
        sleep(1);
        cout << "Манекен от полученных ударов разваливается. \n Вам кажется, "
                "что из его глаз выбежала пара слез."
             << endl;
        sleep(1);
        cout << "- Да, что и следовало ожидать от человека. \n- Ты жесток."
             << endl;
        sleep(1);
        cout << "- Чтож, если ты решил идти по такому пути, то не вини меня, "
                "дружок.\n- Тебе будет очень трудно."
             << endl;
        sleep(1);
        cout << "..." << endl;
        sleep(1);
        cout << endl
             << "Вы просыпаетесь в каком-то лесу. \n Вы были рады "
                "порассматривать окружение, но \n на вас вдруг напал "
                "человек.\n Выглядит он как типичный бандит. "
             << endl;
        train = false;
      }
      if (good_end == 3) {
        system("clear");
        sleep(1);
        cout << "Вам показалось, что манекен улыбнулся вам. \n В следующую "
                "секунду он растворился во тьме."
             << endl;
        sleep(2);
        cout << endl
             << "- Хах, человек. Ты заинтересовал меня. \n- Кажется, ты "
                "понимаешь, что нельзя все решать одними кулаками."
             << endl;
        sleep(2);
        cout << endl
             << "- Но при этом, я вижу, что ты сможешь дать отпор, если "
                "понадобится. \n- Очень инетерсно"
             << endl;
        sleep(2);
        cout << endl
             << "- Пожалуй, я награжу тебя. Дам тебе очки опыта.\n- С их "
                "помощью ты можешь повышать свой уровень и характеристики.\n- "
                "Они очень полезны"
             << endl;
        sleep(1);
        character->xp_current += 300;
        if (character->xp_current >= character->xp_need) {
          character->xp_need *= 3;
          character->lvlmodifier(1);
        }
        train = false;
      }
      if (bad_end == 3) {
        system("clear");
        sleep(1);
        cout << "- Хах." << endl;
        sleep(1);
        cout << "- Ахахах." << endl;
        sleep(2);
        cout << "- Кажется, я ошибся в тебе, человек. \n- Ты ничтожен. "
                "Абсолютно ни на что не годен."
             << endl;
        sleep(4);
        cout << "- Я тебя спас от смерти, перенеся в этот мир.\n- Видимо зря. "
                "Чтож."
             << endl;
        sleep(5);
        system("clear");
        cout << "- ПРОЩАЙ. НАВСЕГДА." << endl;
        character->life = false;
        Sudden_Death();
        train = false;
      }
    }
    Dummy *dummy = new Dummy("Стэн");
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
        enemy_mob); //вызов сценария боя, можно потом переделать этот класс
                    //на "взаимодействие" и в нём вызывать сценарий боя
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

void FurtherDialog() { //Для смены диалогового окна, когда перс говорит ещё
                       //после очищения
  cout << endl << endl << "\t\t\t\t 'Нажмите Enter, для продолжения'";
  int input = getchar();
  while (input != 10) {
    input = getchar();
  }
  return;
}

int main() {
  setlocale(LC_ALL, "Russian");
  srand(time(NULL));
  // system("clear");
  bool fight = false;

  Narrative *narrative = new Narrative();
  Entry_level *entry = new Entry_level();
  if (entry->Awaken_Start() == 66) {
    cout << "Вы не можете заснуть, но продолжаете лежать с закрытыми "
            "глазами."
         << endl;
    sleep(1);
    cout << "Задумавшись о бренности бытия вы решили больше не просыпаться."
         << endl;
    entry->Sudden_Death();
    return 0;
  }

  narrative->Awaken_Start();
  string name = entry->Take_players_name();
  Player *p = new Player(name);
  entry->Stat_Explanation(p);
  entry->Fight_Train(p);
  if (fight == true) {
    Bandit *gary = new Bandit("Gary");
    cout << "Ваш противник" << endl;
    gary->listp();
    sleep(5);
    system("clear");
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
