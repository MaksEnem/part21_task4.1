#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

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



				}
				else if (step_hero == "load") {



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
				std::cout << opponents[0].number_of_opponents << std::endl;
			}
		}
	}
}