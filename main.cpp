#include <iostream>
#include "binaryTree.h"

using Dict = binaryTree;

int main()
{
	Dict dict;

	dict.insert(22, "Jane");
	dict.insert(22, "Mary");
	dict.insert(0, "Harold");
	dict.insert(9, "Edward");
	dict.insert(37, "Victoria");
	dict.insert(4, "Matilda");
	dict.insert(26, "Oliver");
	dict.insert(42, "Elizabeth");
	dict.insert(19, "Henry");
	dict.insert(4, "Stephen");
	dict.insert(24, "James");
	dict.insert(-1, "Edward");
	dict.insert(31, "Anne");
	dict.insert(23, "Elizabeth");
	dict.insert(1, "William");
	dict.insert(26, "Charles");
	dict.insert(54, "Fernando");
	dict.insert(34, "test");
	dict.remove(54);
	dict.remove(57);
	dict.remove(24);
	

	dict.displayTree();

	// std::cout << std::endl;

	// dict.displayTree();
}