#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <functional>
#include <regex>
#include <utility>
#include <cstdlib>
#include <cstdio>

#include "prompt.hpp"

struct Unit {
  std::string name;
  int hp;
  int atk;
};

template <typename T, typename R>
struct GameState {
  R info;
  std::function< R(T) > main;

  R run(T t) {
    this->info = main(t);
    return info;
  }

};


GameState<int, int> Intro = {0, [](int i) {
  prompt("Welcome to Duel! Please press Enter to continue.");
  return i;
}};

GameState<int, int> PickChar = {0, [](int i) {
  using strings = std::vector<std::string>;

  system("cls");
  std::string input;
  while (input != "1" && input != "2") {
    input = prompt(strings{
      "Please input 1 or 2 to select your character.",
      "PLAYER 1: Lenny",
      "PLAYER 2: Kenny"
    });
  }
  return (input == "1");
}};

using BattleInfo = std::tuple<std::vector<Unit>, int>;

GameState<int, BattleInfo> Battle = {
  
  BattleInfo{
    {
      {"Lenny", 10, 1},
      {"Kenny", 10, 1}
    },
    0
  },

  [](int char_choice) -> BattleInfo {
    using strings = std::vector<std::string>;

    Unit u1 = {"Lenny", 10, 1};
    Unit u2 = {"Kenny", 10, 1};
    int turn_no = 0;

    /* Assign player unit. */
    Unit& pu = ((char_choice)? u1 : u2);
    Unit& ou = ((char_choice)? u2 : u1);
    
    std::string input;
    while (u1.hp > 0 && u2.hp > 0) {
      system("cls");

      /* Print the screen. */
      std::printf("PLAYER: {%s, %d, %d}\n", pu.name.c_str(), pu.hp, pu.atk );
      std::printf("OPPONT: {%s, %d, %d}\n", ou.name.c_str(), ou.hp, ou.atk );

      /* Choose a move. */
      input = prompt(strings{
        "Choose a move:",
        "  [1] ATTACK",
        "  [2] STRENGTHEN"
      });
      while (input != "1" && input != "2") {
        input = prompt("INVALID INPUT: ");
      }

      /* Input is now valid. */
      if (input == "1") {
        std::cout << "PLAYER attacks!\n";
        std::cout << "PLAYER hits OPPONT for " << pu.atk << " points!\n";
        ou.hp -= pu.atk;
        std::getline(std::cin, input);
      } else {
        pu.atk += 1;
        prompt("PLAYER musters strength...");
      }
    
      ++turn_no;

      if (turn_no/2 % 2 == 0) {
        ou.atk += 1;
        prompt("OPPONT musters strength...");
      } else {
        std::cout << "OPPONT attacks!\n";
        std::cout << "OPPONT hits PLAYER for " << ou.atk << " points!\n";
        pu.hp -= ou.atk;
        std::getline(std::cin, input);
      }
      ++turn_no;
    } // end while

    std::vector<Unit> units = {u1, u2};

    BattleInfo results {
      units,
      turn_no
    };

    return results;
  }
};


GameState<BattleInfo, int> Outro = {
  0,
  [](BattleInfo results) {
    system("cls");
    auto units = std::get<0>(results);
    if (units[0].hp <= 0) {
      prompt("PLAYER has died.");
    } else if (units[1].hp <= 0) {
      prompt("OPPONT has died.");
    }
    return 0;
  }
};

int main() {
  std::string input;
  /* Menu */
  int i = Intro.run(0);
  /* Pick character. */
  auto char_choice = PickChar.run(i);

  auto results = Battle.run(char_choice);

  Outro.run(results);
  


  return 0;
  /* */
}