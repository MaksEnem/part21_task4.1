#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "../task4(Turn based RPG)/task4.cpp"

struct Ñharacters {

	std::string name;
	int health_points;
	int armor;
	int damage;
	int coordinate_x;
	int coordinate_y;
	bool is_life;
	int number_of_opponents;
};

void initializing_opponents(Ñharacters& opponents, int& i) {

	if (i == 0) {

		std::cout << "Enter your character's name: ";
		std::cin >> opponents.name;

		std::cout << "Enter the number of health points for your character: ";
		std::cin >> opponents.health_points;

		std::cout << "Enter the number of armor for your character: ";
		std::cin >> opponents.armor;

		std::cout << "Enter the number of damage for your character: ";
		std::cin >> opponents.damage;

	}
	else {

		opponents.name = "Opponent#" + std::to_string(i);
		opponents.health_points = std::rand() % 101 + 50;
		opponents.armor = std::rand() % 51;
		opponents.damage = std::rand() % 16 + 15;
		opponents.is_life = true;

	}
	
}

void initializing_fieid(char field[][20]) {

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {

			field[i][j] = '.';
		}
	}
}

void initializing_game_fieid_opponents(Ñharacters& opponents, char field[][20], int& i) {

	if (i == 0) {

		opponents.coordinate_x = 10;
		opponents.coordinate_y = 10;	

	field[opponents.coordinate_x][opponents.coordinate_y] = 'P';

	}
	else {

		do {

			opponents.coordinate_x = std::rand() % 20;
			opponents.coordinate_y = std::rand() % 20;

		} while (field[opponents.coordinate_x][opponents.coordinate_y] != '.');

		field[opponents.coordinate_x][opponents.coordinate_y] = 'E';

	}
}

void playing_field(char field[][20]) {

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 20; ++j) {

			if (field[i][j] == '.') {

				std::cout << "." << " ";

			}
			else if (field[i][j] == 'E') {

				std::cout << "E" << " ";

			}
			else if (field[i][j] == 'P') {

				std::cout << "P" << " ";

			}
		}
		std::cout << std::endl;
	}
}

void hero_damage_opponents(Ñharacters& hero, Ñharacters& opponents) {

	std::cout << opponents.name << " took damage: " << hero.damage;

	opponents.armor -= hero.damage;

	if (opponents.armor < 0) {

		opponents.health_points += opponents.armor;
		opponents.armor = 0;

	}
}

void opponents_damage_hero(Ñharacters& opponents, Ñharacters& hero){

	std::cout << hero.name << " took damage: " << opponents.damage;

	hero.armor -= opponents.damage;

	if (hero.armor < 0) {

		hero.health_points += hero.armor;
		hero.armor = 0;

	}

	std::cout << "hero healt points = " << hero.health_points << std::endl;
}

void save_opponents(std::ofstream& out_file, Ñharacters& opponents, int & j) {

	int len = opponents.name.length();
	out_file.write((char*)&len, sizeof(len));
	out_file.write(opponents.name.c_str(), len);
	out_file.write((char*)&opponents.health_points, sizeof(opponents.health_points));
	out_file.write((char*)&opponents.armor, sizeof(opponents.armor));
	out_file.write((char*)&opponents.damage, sizeof(opponents.damage));
	out_file.write((char*)&opponents.coordinate_x, sizeof(opponents.coordinate_x));
	out_file.write((char*)&opponents.coordinate_y, sizeof(opponents.coordinate_y));	

	if (j ==0) {

		out_file.write((char*)&opponents.number_of_opponents, sizeof(opponents.number_of_opponents));

	}
	else {

		out_file.write((char*)&opponents.is_life, sizeof(opponents.is_life));

	}
}

void load_opponents(std::ifstream& in_file, Ñharacters& opponents, int& j) {

	int len;
	in_file.read((char*)&len, sizeof(len));
	opponents.name.resize(len);
	in_file.read((char*)opponents.name.c_str(), len);
	in_file.read((char*)&opponents.health_points, sizeof(opponents.health_points));
	in_file.read((char*)&opponents.armor, sizeof(opponents.armor));
	in_file.read((char*)&opponents.damage, sizeof(opponents.damage));
	in_file.read((char*)&opponents.coordinate_x, sizeof(opponents.coordinate_x));
	in_file.read((char*)&opponents.coordinate_y, sizeof(opponents.coordinate_y));
	
	if (j == 0) {

		in_file.read((char*)&opponents.number_of_opponents, sizeof(opponents.number_of_opponents));

	}
	else {

		in_file.read((char*)&opponents.is_life, sizeof(opponents.is_life));

	}
}


int main() {

	std::srand(std::time(nullptr));

	Ñharacters opponents[6];

	for (int i = 0; i < 6; ++i) {

		initializing_opponents(opponents[i], i);
		opponents[0].number_of_opponents = i;
	}	

	char field[20][20];

	initializing_fieid(field);

	for (int i = 0; i < 6; ++i) {

		initializing_game_fieid_opponents(opponents[i], field, i);
	}

	bool is_result = true;
	int step;
	std::string step_hero;
	

	while (is_result) {

		for (int i = 0; i < 6; ++i) {

			if (i == 0) {				

				playing_field(field);
				

				do {

					std::cout << "Make a move with the keys: l, r, u, d, or enter \"save/load\": ";
					std::cin >> step_hero;

					
				} while (step_hero != "l" && step_hero != "r" && step_hero != "u" && step_hero != "d" && step_hero != "save" && step_hero != "load");

				if (step_hero == "save") {

					std::ofstream out_file("save.bin", std::ios::binary);

					if (out_file.is_open()) {

						for (int j = 0; j < 6; ++j) {

							save_opponents(out_file, opponents[j], j);

						}

						out_file.close();
						std::cout << "File saved successfully\n";
					}
					else {

						std::cout << "WARNING!\n";
						std::cout << "ERROR!!!\n";
						std::cout << "File is not open\n";

					}

				}
				else if (step_hero == "load") {

					std::ifstream in_file;

					in_file.open("save.bin", std::ios::binary);

					if (in_file.is_open()) {

						std::cout << "File is open\n";

						for (int j = 0; j < 6; ++j) {

							load_opponents(in_file, opponents[j], j);
							
							if (j == 0) {

								std::cout << " number_of_opponents: " << " " << opponents[j].number_of_opponents << std::endl;

							}
							else {

								std::cout << " is_life: " << " " << opponents[j].is_life << std::endl;

							}
						}

						in_file.close();

					}
					else {

						std::cout << "WARNING!\n";
						std::cout << "ERROR!!!\n";
						std::cout << "File is not open\n";

					}

				}else if (step_hero == "l") {

					if (opponents[i].coordinate_y == 0) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_y -= 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

							for (int j = 5; j > 0; --j) {

								if (opponents[j].coordinate_x == opponents[i].coordinate_x && opponents[j].coordinate_y == opponents[i].coordinate_y) {

									hero_damage_opponents(opponents[i], opponents[j]);

									if (opponents[j].health_points > 0) {

										opponents[i].coordinate_y += 1;
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

									}
									else if (opponents[j].health_points <= 0) {

										field[opponents[j].coordinate_x][opponents[j].coordinate_y] == '.';
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';
										opponents[j].is_life = false;
										--opponents[i].number_of_opponents;
										
										if (opponents[i].number_of_opponents <= 0) {

											std::cout << "You victory" << std::endl;
											is_result = false;
										}

									}

									break;
								}
							}

						}
						else {

							field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

						}
					}
				}
				else if (step_hero == "r") {

					if (opponents[i].coordinate_y == 19) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_y += 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

							for (int j = 5; j > 0; --j) {

								if (opponents[j].coordinate_x == opponents[i].coordinate_x && opponents[j].coordinate_y == opponents[i].coordinate_y) {

									hero_damage_opponents(opponents[i], opponents[j]);

									if (opponents[j].health_points > 0) {

										opponents[i].coordinate_y -= 1;
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

									}
									else if (opponents[j].health_points <= 0) {

										field[opponents[j].coordinate_x][opponents[j].coordinate_y] = '.';
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';
										opponents[j].is_life = false;
										--opponents[i].number_of_opponents;										
										playing_field(field);
										
										if (opponents[i].number_of_opponents <= 0) {

											std::cout << "You victory" << std::endl;
											is_result = false;
										}
									}

									break;
								}
							}
						}
						else {

							field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

						}
					}
				}
				else if (step_hero == "u") {

					if (opponents[i].coordinate_x == 0) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_x -= 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

							for (int j = 5; j > 0; --j) {

								if (opponents[j].coordinate_x == opponents[i].coordinate_x && opponents[j].coordinate_y == opponents[i].coordinate_y) {

									hero_damage_opponents(opponents[i], opponents[j]);

									if (opponents[j].health_points > 0) {

										opponents[i].coordinate_x += 1;
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

									}
									else if (opponents[j].health_points <= 0) {

										field[opponents[j].coordinate_x][opponents[j].coordinate_y] = '.';
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';
										opponents[j].is_life = false;
										--opponents[i].number_of_opponents;
										
										if (opponents[i].number_of_opponents <= 0) {

											std::cout << "You victory" << std::endl;
											is_result = false;
										}
									}

									break;
								}
							}
						}
						else {

							field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

						}
					}
				}
				else if (step_hero == "d") {

					if (opponents[i].coordinate_x == 19) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_x += 1;
						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

							for (int j = 5; j > 0; --j) {

								if (opponents[j].coordinate_x == opponents[i].coordinate_x && opponents[j].coordinate_y == opponents[i].coordinate_y) {

									hero_damage_opponents(opponents[i], opponents[j]);

									if (opponents[j].health_points > 0) {

										opponents[i].coordinate_x -= 1;
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

									}
									else if (opponents[j].health_points <= 0) {

										field[opponents[j].coordinate_x][opponents[j].coordinate_y] = '.';
										field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';
										opponents[j].is_life = false;
										--opponents[i].number_of_opponents;
										
										if (opponents[i].number_of_opponents <= 0) {
											
											std::cout << "You victory" << std::endl;
											is_result = false;
										}
									}

									break;
								}
							}
						}
						else {

							field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'P';

						}
					}
				}
				
				std::cout << std::endl;

			}else if (i > 0 && opponents[i].is_life == true) {

				step = std::rand() % 4;

				if (step == 0) {

					if (opponents[i].coordinate_x == 19) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';
						opponents[i].coordinate_x += 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'P') {

							if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'E') {

								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

							}
							else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

								opponents[i].coordinate_x -= 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
						}
						else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'P') {

							if (opponents[i].coordinate_x == opponents[0].coordinate_x && opponents[i].coordinate_y == opponents[0].coordinate_y) {

								opponents_damage_hero(opponents[i], opponents[0]);

							}
							

							if (opponents[0].health_points > 0) {

								opponents[i].coordinate_x -= 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

							}
							else if (opponents[0].health_points <= 0) {

								std::cout << "You lose" << std::endl;
								is_result = false;
								break;
							}

						}
					}
				}
				else if (step == 1) {


					if (opponents[i].coordinate_x == 0) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_x -= 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'P') {

							if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'E') {

								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
							else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

								opponents[i].coordinate_x += 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
						}
						else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'P') {

							if (opponents[i].coordinate_x == opponents[0].coordinate_x && opponents[i].coordinate_y == opponents[0].coordinate_y) {

								opponents_damage_hero(opponents[i], opponents[0]);

							}

							if (opponents[0].health_points > 0) {

								opponents[i].coordinate_x += 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

							}
							else if (opponents[0].health_points <= 0) {

								std::cout << "You lose" << std::endl;
								is_result = false;
								break;
							}
						}
					}
				}
				else if (step == 2) {

					if (opponents[i].coordinate_y == 19) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_y += 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'P') {

							if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'E') {

								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
							else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

								opponents[i].coordinate_y -= 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
						}
						else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'P') {

							if (opponents[i].coordinate_x == opponents[0].coordinate_x && opponents[i].coordinate_y == opponents[0].coordinate_y) {

								opponents_damage_hero(opponents[i], opponents[0]);

							}

							if (opponents[0].health_points > 0) {

								opponents[i].coordinate_y -= 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

							}
							else if (opponents[0].health_points <= 0) {

								std::cout << "You lose" << std::endl;
								is_result = false;
								break;
							}
						}
					}
				}
				else if (step == 3) {

					if (opponents[i].coordinate_y == 0) {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

					}
					else {

						field[opponents[i].coordinate_x][opponents[i].coordinate_y] = '.';

						opponents[i].coordinate_y -= 1;

						if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'P') {

							if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] != 'E') {

								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
							else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'E') {

								opponents[i].coordinate_y += 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';
							}
						}
						else if (field[opponents[i].coordinate_x][opponents[i].coordinate_y] == 'P') {

							if (opponents[i].coordinate_x == opponents[0].coordinate_x && opponents[i].coordinate_y == opponents[0].coordinate_y) {

								opponents_damage_hero(opponents[i], opponents[0]);

							}

							if (opponents[0].health_points > 0) {

								opponents[i].coordinate_y += 1;
								field[opponents[i].coordinate_x][opponents[i].coordinate_y] = 'E';

							}
							else if (opponents[0].health_points <= 0) {

								std::cout << "You lose" << std::endl;
								is_result = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}