#include <iostream>
#include <fstream>
#include <string>

struct Save {
  char player[100];
  int score;
};

struct Coordinates {
    int x;
    int y;
};

int main() {
    std::ifstream dataRp("Replay.bin", std::ios::binary);
    std::ofstream dataRpW("Replay.bin", std::ios::binary | std::ios::app);

    std::ifstream dataLb("Leaderboard.bin", std::ios::binary);

    std::string file;
    std::cin >> file;

    if (file == "lb") {
        Save temp;

        while (dataLb.read((char *) &temp, sizeof(Save))) {
            std::cout << "Player: " << temp.player << ", score: " << temp.score << "\n";
        }
    } else if (file == "rp") {
        if (!dataRp.is_open()) return 0;
        
        std::string action;
        std::cin >> action;

        if (action == "write") {
            Coordinates newCoord;

            std::cin >> newCoord.x >> newCoord.y;
            dataRpW.write((char*) &newCoord, sizeof(Coordinates));
        } else if (action == "read") {
            Coordinates temp;

            while (dataRp.read((char*)&temp, sizeof(Coordinates))) {
	            std::cout << "x: " << temp.x << ", y: " << temp.y << "\n";
            }     
        }
    }

    return 0;
}
