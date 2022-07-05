#include"binaryTree.h"
struct binaryTree::Node
{
	KeyType key;
	ItemType item;
	Node* leftChild;
	Node* rightChild;

	binaryTree::Node()
	{
		key = 0;
		item = "";
	}

};



binaryTree::binaryTree(const binaryTree& originalTree)
{
	this->root = deepCopy(originalTree.root);
}

binaryTree& binaryTree::operator=(const binaryTree& original)
{
	deepDelete(this->root);
	this->root = deepCopy(original.root);
	if (this == &original)return *this;
}

binaryTree::binaryTree(binaryTree && originalTree)
{
	deepDelete(this->root);
	this->root = originalTree.root;
	originalTree.root = leaf();
}

binaryTree& binaryTree::operator=(binaryTree&& originalTree)
{
	deepDelete(this->root);
	this->root = originalTree.root;
	originalTree.root = leaf();
	return *this;
}

binaryTree::~binaryTree()
{
	//deepDelete(root);
}


binaryTree::ItemType* binaryTree::lookUp(KeyType key)
{
	/*Node* look = root;
	if (key == root->key) {
		return &root->item;
	}
	while (!isLeaf(look)) {
		if (key>look->key)
		{
			look = look->rightChild;
		}
		else if (key<look->key)
		{
			look = look->leftChild;
		}
		else if (key == look->key)
		{
			cout << "found the right item" << endl;
			return &root->item;
		}
		
	}
	cout << "item not in tree" << endl;*/

	
	return lookupRec(key, root);

}

binaryTree::ItemType* binaryTree::lookupRec(KeyType soughtKey, Node* currentNode)
{
	if (isLeaf(currentNode))
	{
		
		cout << "The item you are looking for is not in the tree :(" << endl;
		
	}
	else
	{
		// Whatever is to be done at an internal node
		if (soughtKey > currentNode->key) {
			lookupRec(soughtKey, currentNode->rightChild);
		}
		else if(soughtKey < currentNode->key){
			lookupRec(soughtKey, currentNode->leftChild);
		}
		else {
			cout << currentNode->item << endl;
			return &currentNode->item;
		}
	}
}

void binaryTree::insert(KeyType key, ItemType item)
{
	Node* insert = new Node;
	insert->item = item;
	insert->key = key;
	insert->leftChild = leaf();
	insert->rightChild = leaf();
	Node* checkNull = root;
	
	if (isLeaf(root)) {
		
		root = insert;
		std::cout << "inserted root" << std::endl;
	}
	else
	{
		while (!isLeaf(checkNull)) {
			if (checkNull->key == key) {
				checkNull->item = item;
				break;
			}
			else if (key < checkNull->key && isLeaf(checkNull->leftChild))
			{
				checkNull->leftChild = insert;
				break;
			}
			else if (key < checkNull->key)
			{
				checkNull = checkNull->leftChild;
			}
			else if (key > checkNull->key && isLeaf(checkNull->rightChild))
			{	
				checkNull->rightChild = insert;
				break;
			}
			else
			{
				checkNull = checkNull->rightChild;
			}
		}
	}


}

void binaryTree::insertRec(KeyType k, ItemType i, Node*& current)
{
	// worker definition goes here
}


void binaryTree::remove(KeyType key)
{
	removeRec(key, root);
}


void binaryTree::removeRec(KeyType key, Node*& curr)
{
	if (!isLeaf(curr))
	{
		if (key > curr->key) {
			removeRec(key, curr->rightChild);
		}
		else if (key < curr->key) {
			removeRec(key, curr->leftChild);
		}
		else if (key == curr->key){
			if (isLeaf(curr->leftChild) && isLeaf(curr->rightChild)) {
				delete curr;
				curr = nullptr;
			}
			else if (isLeaf(curr->leftChild)) {
				Node* temp = curr;
				curr = curr->rightChild;
				delete temp;
			}
			else if(isLeaf(curr->rightChild)){
				Node* temp = curr;
				curr = curr->leftChild;
				delete temp;
			}
			else{
				Node* temp = detachMinimumNode(curr->rightChild);
				curr->key = temp->key;
				curr->item = temp->item;
				removeRec(curr->key, curr->rightChild);
			}
		}
	}
}


binaryTree::Node* binaryTree::detachMinimumNode(Node*& curr)
{
	while (curr->leftChild != leaf()) {
		curr = curr->leftChild;
	}
	return curr;
}

void binaryTree::deepDelete(Node*curr)
{
	if (!isLeaf(curr)) {
		deepDelete(curr->leftChild);
		deepDelete(curr->rightChild);
		delete curr;
	}
}

binaryTree::Node* binaryTree::deepCopy(Node* originalNode)
{
	Node* root = originalNode;
	if (!isLeaf(originalNode)) {
		root->leftChild = deepCopy(originalNode->leftChild);
		root->rightChild = deepCopy(originalNode->rightChild);
	}
	return root;

}


void binaryTree::displayEntries()
{
	displayEntriesRec(root);
}


void binaryTree::displayEntriesRec(Node*root)
{
	if (!isLeaf(root)) {
		displayEntriesRec(root->leftChild);
		cout << root->key << ", " << root->item << endl;
		displayEntriesRec(root->rightChild);
	}
}

void binaryTree::displayTree()
{
	displayTreeRec(root," ");
}

void binaryTree::removeIf(std::function<bool(KeyType)>)
{
}


void binaryTree::displayTreeRec(Node*  root, string tab)
{
	
	string indnt = "\t";
	if (!isLeaf(root)) {
		indnt += tab;
		cout << indnt << root->key << ", " << root->item << endl;
		displayTreeRec(root->leftChild, indnt);
		displayTreeRec(root->rightChild, indnt);
	}
	else {
		indnt += tab;
		cout << indnt << "Leaf" << endl;
	}
}


binaryTree::Node* binaryTree::leaf()
{
	return nullptr;
}

bool binaryTree::isLeaf(Node* n)
{
	return (n == nullptr);
}


