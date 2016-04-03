#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "WordPuzzle.h"

std::unordered_map<std::string, std::vector<std::pair<int, int>>> solutionTable = std::unordered_map<std::string, std::vector<std::pair<int, int>>>();

void solve_puzzle_rec_helper(std::vector<std::pair<int, int>> positions, std::string currWord, word_node* curr_node, std::pair<int, int> pos, std::vector<std::vector<char>> puzzle, word_node* trie, bool visited[BOARD_SIZE][BOARD_SIZE])
{
	if (curr_node->isValidWord)
	{
		solutionTable.insert({ currWord, positions });
	}
	if (curr_node->children.empty())
	{
		return;
	}
	for (int i = pos.first - 1; i < pos.first + 2; i++)
	{
		for (int j = pos.second - 1; j < pos.second + 2; j++)
		{
			if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE && visited[i][j] == false)
			{
				char currLetter = tolower(puzzle[i][j]);

				if (curr_node->children.find(currLetter) != curr_node->children.end())
				{
					std::pair<int, int> test_pos(i, j);
					visited[i][j] = true;
					positions.push_back(test_pos);
					currWord += currLetter;
					word_node* test_node = curr_node->children[currLetter];

					solve_puzzle_rec_helper(positions, currWord, test_node, test_pos, puzzle, trie, visited);
					
					currWord.pop_back();
					visited[i][j] = false;
					positions.pop_back();
				}
			}
		}
	}
}

void solve_puzzle(std::vector<std::vector<char>> puzzle, word_node* trie)
{
	for (int i = 0; i < puzzle.size(); i++)
	{
		for (int j = 0; j < puzzle[i].size(); j++)
		{
			char curr = tolower(puzzle[i][j]);

			std::pair<int, int> pos(i, j);
			std::vector<std::pair<int, int>> positions;
			positions.push_back(pos);

			bool visited[BOARD_SIZE][BOARD_SIZE];
			init_visited(visited);

			visited[i][j] = true;

			word_node* curr_node = trie->children[curr];

			std::string currWord = "";
			currWord += curr;

			solve_puzzle_rec_helper(positions, currWord, curr_node, pos, puzzle, trie, visited);
		}
	}
}

word_node* create_word_trie(std::vector<std::string>& dict)
{
	word_node* root = new word_node();
	word_node* curr = root;

	for (int i = 0; i < dict.size(); i++)
	{
		std::string word = dict[i];
		if (word.length() > 2 && word.length() < BOARD_SIZE*BOARD_SIZE + 1)
		{
			for (int j = 0; j < word.size(); j++)
			{
				if (!curr->children[word[j]])
				{
					curr->children[word[j]] = new word_node();
					if (j == word.length() - 1)
					{
						curr->children[word[j]]->isValidWord = true;
					}
				}
				curr = curr->children[word[j]];
			}
		}
		curr = root;
	}

	return root;
}

void free_word_trie(word_node* root)
{
	if (root == NULL)
	{
		return;
	}

	for (auto it = root->children.begin(); it != root->children.end(); it++)
	{
		free_word_trie(it->second);
	}

	delete root;
}

std::vector<std::vector<char>> init_puzzle(std::string filename)
{
	std::vector<std::vector<char>> puzzle;
	std::ifstream puzzle_file(filename.c_str());
	std::string line;
	int lineNum = 0;
	while (getline(puzzle_file, line))
	{
		puzzle.push_back(std::vector<char>());
		for (int i = 0; i < line.size(); i++)
		{
			char curr = line[i];
			if (curr != ' ' && curr != '\t')
			{
				puzzle[lineNum].push_back(curr);
			}
		}
		lineNum++;
	}
	puzzle_file.close();
	return puzzle;
}

std::vector<std::string> init_dictionary(std::string filename)
{
	std::vector<std::string> dict;
	std::ifstream dict_file(filename);
	std::string line;
	while (getline(dict_file, line))
	{
		dict.push_back(line);
	}
	dict_file.close();
	return dict;
}

void init_visited(bool visited[][BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			visited[i][j] = false;
		}
	}
}