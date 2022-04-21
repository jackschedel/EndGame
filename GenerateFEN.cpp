#include "GenerateFEN.h"
using namespace std;

GenerateFEN::GenerateFEN(std::string file_name)
{
	ifstream file(file_name); //"mate_in_lichess_db_puzzles.csv"
	string line;
	while (getline(file, line))
	{
		if (line.find("mateIn2") != UINT_MAX) //change this for mate in 3 or 2
		{
			mateIn_X.push_back(line);
		}
	}
	file.close();
}
GenerateFEN::GenerateFEN()
{
	;
}

///output FEN, 1st move
pair<std::string, std::string> GenerateFEN::randomFEN()
{
	int index = rand() % mateIn_X.size();
	string FEN, move;
	unsigned int pos = 0;

	string line = mateIn_X[index];
	string useless = line.substr(pos, line.find(',', pos));
	pos = line.find(',', pos) + 1;
	FEN = line.substr(pos, line.find(',', pos) - pos);
	pos = line.find(',', pos) + 1;
	string all_moves = line.substr(pos, line.find(',', pos) - pos);
	move = all_moves.substr(0, all_moves.find(' '));

	return pair<string, string>(FEN, move);
}


