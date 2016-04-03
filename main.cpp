#include "WordPuzzle.h"
#include <iostream>

//r/TheHappieMakers Word Puzzle Challenge Part 1 & Part 2

int main(int argc, char** argv)
{
	std::vector<std::string> dict = init_dictionary("wordlist.txt");
	word_node* trie = create_word_trie(dict);

	std::vector<std::vector<char>> puzzle = init_puzzle("puzzle.txt");
	solve_puzzle(puzzle, trie);

	std::string word_bank[12] = { "january", "february", "march", "april",
	"may", "june", "july","august", "september","october","november","december" };

	for (int i = 0; i < 12; i++)
	{
		std::cout << word_bank[i].c_str() << std::endl;
		std::pair<int, int> pos = solutionTable[word_bank[i]][0];
		std::cout << "Row: " << pos.first << " Column: " << pos.second << std::endl;
	}

	free_word_trie(trie);
	return 0;
}