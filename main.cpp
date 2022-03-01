#include <iostream>
#include "RBTreeDictionary.hpp"
#include <string>
#include <chrono>

void assimptoticTest();

int main()
 {
	srand(0);
	RBTreeDictionary dictionary("a","letter");
	dictionary.insert("a", "word");
	dictionary.insert("b", "letter");
	dictionary.insert("c", "letter");
 	dictionary.insert("d", "letter");
	dictionary.insert("e", "letter");
	dictionary.insert("f", "letter");
	dictionary.insert("g", "letter");
	dictionary.insert("h", "letter");
	dictionary.insert("i", "letter");
	dictionary.deleteWord("c");
	dictionary.deleteWord("d");
	dictionary.deleteWord("i");
	dictionary.deleteWord("b");
	dictionary.printDictionary(std::cout);
	dictionary.printWord("c", std::cout);
	dictionary.printWord("a", std::cout);
	std::cout << "\nIs word \"a\" in the dictionary : "
		<< ((dictionary.search("a")) ? "Yes\n" : "No\n");
	std::cout << "\nIs word \"b\" in the dictionary : "
		<< ((dictionary.search("b")) ? "Yes\n" : "No\n");
	assimptoticTest();
	return 0;
}

void assimptoticTest()
{
	int size = 2000;
	RBTreeDictionary dictionaryAssimptTest1;
	auto startInsert = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		dictionaryAssimptTest1.insert(std::to_string(rand()), "smth");
	}
	auto endInsert = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> timeForInsert = endInsert - startInsert;
	std::cout << "\tInsert to tree duration: " << timeForInsert.count() * 1000 << " ms" << "\n";
	auto startSearch = std::chrono::high_resolution_clock::now();
	dictionaryAssimptTest1.search("a");
	auto endSearch = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> timeForSearch = endSearch - startSearch;
 	std::cout << "\tSearch in tree duration: " << timeForSearch.count() * 1000000 << " ns" << "\n";

	RBTreeDictionary dictionaryAssimptTest2;
	for (int i = 0; i < size; i++)
	{
		dictionaryAssimptTest2.insert(std::to_string(i), "smth");
	}
	auto startDelete = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)
	{
		dictionaryAssimptTest2.deleteWord(std::to_string(i));
	}
	auto endDelete = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> timeForDelete = endDelete - startDelete;
	std::cout << "\tDelete from tree duration: " << timeForDelete.count() * 1000 << " ms" << "\n";
}
