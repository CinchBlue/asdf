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

struct Unit {
  std::string name;
  int hp;
  int atk;
};     

int main() {
  Unit u1 = {"Lenny", 10, 1};
  Unit u2 = {"Kenny", 10, 1};

  std::string input;
  /* Menu */
  std::cout << "Welcome to Duel! Please press Enter to continue.\n";
  std::getline(std::cin, input);

  /* Pick character. */
  system("cls");
  while (input != "1" && input != "2") {
    std::cout << "Please input 1 or 2 to select your character.\n";
    std::cout << "PLAYER 1: Lenny\n";
    std::cout << "PLAYER 2: Kenny\n";
    std::getline(std::cin, input);
  }

  /* Assign player unit. */
  Unit& pu = ((input == "1")? u1 : u2);
  Unit& ou = ((input == "1")? u2 : u1);
  
  int turn_no = 0;
  while (u1.hp > 0 && u2.hp > 0) {
    system("cls");

    /* Print the screen. */
    std::printf("PLAYER: {%s, %d, %d}\n", pu.name.c_str(), pu.hp, pu.atk );
    std::printf("OPPONT: {%s, %d, %d}\n", ou.name.c_str(), ou.hp, ou.atk );

    /* Choose a move. */
    std::cout << "Choose a move:\n";
    std::cout << "  [1] ATTACK\n";
    std::cout << "  [2] STRENGTHEN\n";
    std::getline(std::cin, input);
    while (input != "1" && input != "2") {
      std::cout << "INVALID INPUT: ";
      std::getline(std::cin, input);
    }
    /* Input is now valid. */
    if (input == "1") {
      std::cout << "PLAYER attacks!\n";
      std::cout << "PLAYER hits OPPONT for " << pu.atk << " points!\n";
      ou.hp -= pu.atk;
      std::getline(std::cin, input);
    } else {
      std::cout << "PLAYER musters strength...\n";
      pu.atk += 1;
      std::getline(std::cin, input);
    }
  
    ++turn_no;

    if (turn_no/2 % 2 == 0) {
      std::cout << "OPPONT musters strength...\n";
      ou.atk += 1;
      std::getline(std::cin, input);
    } else {
      std::cout << "OPPONT attacks!\n";
      std::cout << "OPPONT hits PLAYER for " << ou.atk << " points!\n";
      pu.hp -= ou.atk;
      std::getline(std::cin, input);
    }
    ++turn_no;
  }

  if (pu.hp <= 0) {
    std::cout << "PLAYER is dead.\n";
  } else if (ou.hp <= 0) {
    std::cout << "OPPONT is dead.\n";
  }
  std::getline(std::cin, input);

  return 0;
  /* */
}