#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>
#include "entities/entity.h"
#include "entities/player.h"
#include "items/armor.h"
#include "items/weapon.h"
#include "structures/dungeon.h"
#include "structures/shop.h"

void print(std::string text) {
    /**
     * Clears out the terminal/console and prints wrapped text
     * Current line length: 60 chars
     * @param text: the text to print out
     */
    system("clear");
    int text_index = 0;
    std::string word;
    int line_size = 0;
    while (text_index < text.size()) { // Traverse each char in text until the end is reached
        word += text[text_index]; // Add the char to the current word
        if (text[text_index] == '\n') { // Newline = end of current line and word
            line_size = 0;
            std::cout << word; // Print out word before resetting it
            word = "";
        } else if (text[text_index] == ' ') { // Space = end of current word
            if (line_size + word.length() > 60) { // word can't fit in current line
                line_size = word.length(); // Word is at start of next line
                std::cout << std::endl; // Move to next line
            } else {line_size += word.length();} // Word can fit in current line
            std::cout << word; 
            word = "";
        }
        ++text_index; // Move to next char
    }
    std::cout << word; // Print out last word (ends with '\0')
}

int main(void) {
    // Setup player
    std::string name;
    print("DUNGEON OUTSKIRTS\n\nYou wake up in a daze, surrounded by a desolate wasteland with nothing interesting in sight apart from a big black door. You approach it and decide to see where it goes. As you push it open, a question pops into your mind:\n\n\"What was my name again?\"\n>>");
    std::getline(std::cin, name);
    Player player(name);
    // Setup shop
    Shop shop(&player);
    // Main game loop
    std::string choice;
    std::vector<std::tuple<std::string, bool, bool>> dungeons = { // Dungeon Name, Unlocked, Completed
                                                    {"THE GOBLIN DUNGEON", true, false},
                                                    {"THE REPTILE DUNGEON", false, false},
                                                    {"THE BEAST DUNGEON", false, false},
                                                    {"THE UNDEAD DUNGEON", false, false},
                                                    {"THE MYSTERY DUNGEON", false, false}
                                                 };
    while (choice != "q") { // Until player quits the game
        player.rest();
        print("THE HAVEN\n\nYou walk into a room with gray walls. On both sides of you are two black doors similar to the one you just walked through. In front of you is a shopkeeper's booth next to a mysterious white door.\n\nShopkeeper: \"Welcome, adventurer! Can I interest you in some wares before you venture through those dungeon doors?\"\n\n");
        for (int i = 0; i < dungeons.size(); ++i) {
            std::cout << i + 1 << " - " << std::get<0>(dungeons[i]);
            if (std::get<1>(dungeons[i]) == false) {std::cout << " (LOCKED)";}
            else if (std::get<2>(dungeons[i]) == true) {std::cout << " (COMPLETE!)";}
            std::cout << std::endl;
        }
        std::cout << "s - Go to Shop\ni - Open Inventory\nq - Quit Game\n>>";
        std::getline(std::cin, choice);
        if ((choice == "1") && (std::get<2>(dungeons[0]) == false)) { // Door #1
            std::vector<std::tuple<std::string, int, int, int>> enemies = {
                                                                            {"Goblin", 50, 2, 4},
                                                                            {"Goblin Warrior", 100, 5, 10},
                                                                            {"Goblin Archer", 75, 3, 6},
                                                                            {"Hobgoblin", 125, 8, 16}
                                                                          };
            Dungeon dun1(std::get<0>(dungeons[0]), 10, 20, &player, enemies, 1);
            dun1.explore();
            if (!player.is_dead()) {
                std::get<2>(dungeons[0]) = std::get<1>(dungeons[1]) = true;
                player.power_up();
            }
        } 
        else if ((choice == "2") && (std::get<2>(dungeons[0]) == true) && (std::get<2>(dungeons[1]) == false)) { // Door #2
            std::vector<std::tuple<std::string, int, int, int>> enemies = {
                                                                            {"Kobold", 125, 4, 8},
                                                                            {"Lizard Warrior", 175, 10, 20},
                                                                            {"Troglodyte", 150, 6, 12},
                                                                            {"Winged Serpent", 100, 3, 6},
                                                                            {"Behir", 225, 16, 32}
                                                                          };
            Dungeon dun2(std::get<0>(dungeons[1]), 12, 24, &player, enemies, 2);
            dun2.explore();
            if (!player.is_dead()) {
                std::get<2>(dungeons[1]) = std::get<1>(dungeons[2]) = true;
                player.power_up();
            }
        } 
        else if ((choice == "3") && (std::get<2>(dungeons[1]) == true) && (std::get<2>(dungeons[2]) == false)) { // Door #3
            std::vector<std::tuple<std::string, int, int, int>> enemies = {
                                                                            {"Werewolf", 180, 15, 30},
                                                                            {"Chimera", 350, 32, 64},
                                                                            {"Griffin", 240, 25, 50},
                                                                            {"Rabid Ape", 165, 8, 16},
                                                                            {"Sphinx", 225, 20, 40},
                                                                            {"Moonbear", 200, 12, 24}
                                                                          };
            Dungeon dun3(std::get<0>(dungeons[2]), 14, 28, &player, enemies, 3);
            dun3.explore();
            if (!player.is_dead()) {
                std::get<2>(dungeons[2]) = std::get<1>(dungeons[3]) = true;
                player.power_up();
            }
        }
        else if ((choice == "4") && (std::get<2>(dungeons[2]) == true) && (std::get<2>(dungeons[3]) == false)) { // Door #4
            std::vector<std::tuple<std::string, int, int, int>> enemies = {
                                                                            {"Vampire", 500, 20, 40},
                                                                            {"Lich", 1000, 50, 100},
                                                                            {"Poltergeist", 225, 9, 18},
                                                                            {"Banshee", 300, 13, 26},
                                                                            {"Wraith", 350, 15, 30}
                                                                          };
            Dungeon dun4(std::get<0>(dungeons[3]), 15, 30, &player, enemies, 4);
            dun4.explore();
            if (!player.is_dead()) {
                std::get<2>(dungeons[3]) = std::get<1>(dungeons[4]) = true;
                player.power_up();
            }
        } 
        else if ((choice == "5") && (std::get<2>(dungeons[3]) == true) && (std::get<2>(dungeons[4]) == false)) { // Mystery Door (Boss Fight)
            print(std::get<0>(dungeons[4]) + "?\n\nAs you walk through the door, the Shopkeeper follows you in and closes the door behind him.\n\nShopkeeper: \"Well well well, look who completed all the dungeons! I must say I'm impressed, I didn't think you'd make it this far!\"\n\n\"That being said, you were probably expecting another dungeon here, right? Wrong. Heh heh heh heh heh....\"\n\nThe Shopkeeper begins transforming in front of you, slowly but surely resembling the shape of a ... dragon?\n\nBalathar: \"Allow me to reintroduce myself, adventurer: I am Balathar the Gilded, and for your final challenge you shall face me in a battle to the death. If you win, you get to go on with your adventures. If I win, I get to keep your soul. Do we have a deal?\"\n\nPress Enter to Continue\n>>");
            std::getline(std::cin, choice);
            print("BOSS FIGHT\n\nBalathar: \"Remember those Skills you collected? Let's put them to good use, shall we?\"\n\nYou feel a strange tingle in your body as the dragon shoots a beam of blue light at you.\n\nSkills can now be cast at will with no costs!\n\nPress Enter to Continue\n>>");
            std::getline(std::cin, choice);
            Entity boss("Balathar the Gilded Dragon", 5000, 0, 0);
            std::string player_action;
            std::vector<std::tuple<std::string, std::string>> boss_moves = {
                                                                               {"1", "Balathar is hardening himself into stone.\n"},
                                                                               {"1", "Balathar is crystallizing himself for protection.\n"},
                                                                               {"1", "Balathar is forming an outer shell made of steel.\n"},
                                                                               {"2", "Balathar is attempting to heal himself.\n"},
                                                                               {"2", "Balathar is gathering life energy to regenerate.\n"},
                                                                               {"2", "Balathar is generating life force to recover.\n"},
                                                                               {"3", "Balathar is coiling up for a devastating strike.\n"},
                                                                               {"3", "Balathar is preparing to unleash havoc on you.\n"},
                                                                               {"3", "Balathar is getting ready to slam into you.\n"},
                                                                               {"4", "Balathar is generating soul energy to blast you.\n"},
                                                                               {"4", "Balathar is preparing to beam soul energy at you.\n"},
                                                                               {"4", "Balathar is charging up to blast you with soul energy.\n"},
                                                                           };
            std::string boss_action;
            while ((!player.is_dead()) && (!boss.is_dead())) {
                player_action = "You ready yourself for Balathar's next action.\n";
                std::random_device rd; // RNG
                std::mt19937 mt(rd()); // Mersenne Twister 19937 pseudo-generator
                std::uniform_int_distribution<int> move_index(0, boss_moves.size() - 1);
                int m = move_index(mt);
                std::tuple<std::string, std::string> boss_move = boss_moves[m];
                boss_action = std::get<1>(boss_move);
                print("BOSS FIGHT\n\n" + player_action + boss_action + "\n");
                boss.print_enc_stats();
                std::cout << std::endl;
                player.print_enc_stats();
                std::cout << "\nSkills:\n1 - Great Slash\n2 - Life Steal\n3 - Tough Scales\n4 - Soul Blast\n>>";
                std::getline(std::cin, choice);
                if (choice == std::get<0>(boss_move)) { // Player counters boss action
                    if (choice == "1") {player_action = "You slash through Balathar's defensive shell.\n";} 
                    else if (choice == "2") {player_action = "You steal Balathar's generated life force.\n";}
                    else if (choice == "3") {player_action = "You block Balathar's attack and take no damage.\n";}
                    else if (choice == "4") {player_action = "You overpower Balathar's soul beam with your own.\n";}
                    boss_action = "Balathar is stunned. Hit him now!\n";
                    int num_hits = 0;
                    while ((num_hits < 5) && (!boss.is_dead())) {
                        print("BOSS FIGHT\n\n" + player_action + boss_action + "\n");
                        boss.print_enc_stats();
                        std::cout << std::endl;
                        player.print_enc_stats();
                        std::cout << "\nPress Enter to Attack\n>>";
                        std::getline(std::cin, choice);
                        boss.take_dmg(player.get_rand_dmg());
                        ++num_hits;
                    }
                }
                else { // Player fails to counter boss action
                    player_action = "You cast your skill, but Balathar is unaffected.\n";
                    if (std::get<0>(boss_move) == "1") {boss_action = "Balathar emerges from your attack unharmed.\n";} 
                    else if (std::get<0>(boss_move) == "2") {
                        boss_action = "Balathar recovers his health to full.\n";
                        boss.rest();
                    }
                    else if (std::get<0>(boss_move) == "3") { // Player 
                        boss_action = "Balathar unleashes a devastating attack upon you.\n";
                        // Give players a chance to let their DEF block it
                        player.take_dmg(1000000);
                    }
                    else {
                        boss_action = "Balathar blasts you with a powerful beam of soul energy.\n";
                        // Eats through shield and kills player instantly
                        player.take_dmg(1000000);
                        player.take_dmg(1000000);
                    } 
                    print("BOSS FIGHT\n\n" + player_action + boss_action + "\n");
                    boss.print_enc_stats();
                    std::cout << std::endl;
                    player.print_enc_stats();
                    std::cout << "\nPress Enter to Continue\n>>";
                    std::getline(std::cin, choice);
                }
            }
            if (!player.is_dead()) { // Player beats boss fight, game ends here
                print("BOSS FIGHT\n\n" + player_action + boss_action + "\n");
                boss.print_enc_stats();
                std::cout << std::endl;
                player.print_enc_stats();
                std::cout << "\nYou have successfully defeated Balathar the Gilded!\nPress Enter to Continue\n>>";
                std::getline(std::cin, choice);                
                print("THE HAVEN\n\nYour final strike sends Balathar falling to the ground. As his body begins to disintegrate, he turns to look at you with a proud expression on his face before closing his eyes and fading away.\n\nBalathar: \"So long, adventurer. May we meet in another life.\"\n\nA crystal orb lies where Balathar once did, glowing a bright purple. As you pick it up and peer inside it, you see what appears to be snippets of your future. A pirate ship, an old mansion, and ... a red cloak with blue flames? You shake your head out of confusion and stuff the orb into your bag.\n\nPerhaps it is time to leave this Haven and journey elsewhere. Who knows what the future has in store for an adventurer like you?\n\nPress Enter to End Game (Thank You For Playing!)\n>>");
                std::getline(std::cin, choice);
                break; 
            }
            else { // Player fails boss fight
                print("BOSS FIGHT\n\n" + player_action + boss_action + "\n");
                boss.print_enc_stats();
                std::cout << std::endl;
                player.print_enc_stats();
                std::cout << "\nYou have been knocked out.\nPress Enter to Revive\n>>";
                std::getline(std::cin, choice);
            }
        }
        else if (choice == "s") { // Shop
            while (choice != "b") { // Until we go back to the Haven
                print("SHOP\n\nYou walk up to the shopkeeper's booth. In front of him are all sorts of weapons, armors, and potions being displayed for sale.\n\nShopkeeper: \"Take a look at my wares, adventurer! See anything interesting?\"\n\n1 - Buy Weapons\n2 - Buy Armors\n3 - Buy Potions\nt - Talk\nb - Back to Haven\n>>");
                std::getline(std::cin, choice);
                if (choice == "1") {shop.view_weapons();}
                else if (choice == "2") {shop.view_armors();}
                else if (choice == "3") {shop.view_potions();}
                else if (choice == "t") { // Talk to Shopkeeper
                    print("SHOP\n\nShopkeeper: \"You wanna know more about those doors? Each one leads to a different challenge, or should I say, dungeon. Each dungeon will give you a special Skill upon completion. Be careful though, each dungeon is filled with deadly enemies!\"\n\n\"As for that mystery door next to me, that's a special kind of challenge, heh heh. Complete the main four dungeons in here to gather all the abilities and maybe you'll stand a chance! Good luck, adventurer!\"\n\nPress Enter to Continue\n>>");
                    std::getline(std::cin, choice);
                }
            }
        }
        else if (choice == "i") {player.open_inventory();} // Open Inventory
    }
    return 0;
}