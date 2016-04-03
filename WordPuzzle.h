#pragma once
#include <unordered_map>
#include <vector>
#define BOARD_SIZE 50

extern std::unordered_map<std::string, std::vector<std::pair<int, int>>> solutionTable;

/*
* A trie node that has a reference to its children, and whether it is the end of a word.
*/
struct word_node
{
	bool isValidWord;
	std::unordered_map<char, word_node*> children;
};

/*
* Finds all possible words in word search puzzle. Returns solutionTable that takes word as a key,
* returns position of starting letter. Example: solutionTable["January"] -> (x, y)
*/
void solve_puzzle(std::vector<std::vector<char>> puzzle, word_node* trie);

void solve_puzzle_rec_helper(std::vector<std::pair<int, int>> positions, std::string currWord, word_node* curr_node, std::pair<int, int> pos, std::vector<std::vector<char>> puzzle, word_node* trie, bool visited[BOARD_SIZE][BOARD_SIZE]);

/*
* Processes dictionary structure to create a trie structure to be used as a look-up table. This only
* needs to be run once for many solutions.
*/
word_node* create_word_trie(std::vector <std::string> &dict);

/*
* Deletes the word trie.
*/
void free_word_trie(word_node* root);

/*
* Processes puzzle file and pushes all chars to 2-D vector.
*/
std::vector<std::vector<char>> init_puzzle(std::string filename);

/*
* Processes dictionary text file and pushes all strings to a vector.
*/
std::vector<std::string> init_dictionary(std::string filename);

/*
* Initializes the visited matrix so all values are false.
*/
void init_visited(bool visited[BOARD_SIZE][BOARD_SIZE]);