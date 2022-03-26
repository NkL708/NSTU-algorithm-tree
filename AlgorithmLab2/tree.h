#pragma once
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>

template <typename Data, typename Key>
class Tree
{
	struct Item
	{
		Key key;
		Data data;
		Item* right;
		Item* left;
		Item* parent;
		int consoleW;
		Item(Key key, Data data = nullptr, Item* right = nullptr, Item* left = nullptr, Item* parent = nullptr, int consoleW = 0);
	};

	void print_Lt_Rt_t(Item*& root);
	Tree<Data, Key>::Item* lt_Rt_t(Item*& root);
public:
	int viewedItems = 0;
	int size = 0;
	Item* root = nullptr;

	Tree();															// �����������
	~Tree();														// ����������
	int getSize();													// ��������� �������
	void clear(Item*& root);										// �������
	bool isEmpty();													// �������� �� �������
	Data read(Key key, Item*& root);								// ������ ��������
	void edit(Key key, Data newData, Item*& root);					// ��������� ��������
	void add(Key key, Data data, Item*& root, Item*& parent);		// ���������� ��������
	void deleteItem(Key key, Item*& root);							// �������� ��������
	void printHorizontal(Item*& root, int indent = 0);				// ����� ��������������
	void printVertical(Item*& root);								// ����� ������������
	void t_Lt_Rt(Item*& root);
	int getTreeHeight(Item*& root);									// ��������� ������ ������
	int getDepth(Item*& target);									// ��������� ������ ��������
	bool isContain(Key key, Item*& root);							// �������� �� ������ ��������
	int getViewedItems();

	class Iterator
	{
	public:
		Item* obj;
		Data& operator*();
		void operator++(int);
		void operator--(int);
		bool operator ==(const Iterator& it);
		bool operator !=(const Iterator& it);
	};
	Iterator begin();
	Iterator end();

	class ReverseIterator
	{
	public:
		Item* obj;
		Data& operator*();
		void operator++(int);
		void operator--(int);
		bool operator ==(const ReverseIterator& it);
		bool operator !=(const ReverseIterator& it);
	};
	ReverseIterator rBegin();
	ReverseIterator rEnd();
};

template<typename Data, typename Key>
inline Tree<Data, Key>::Item::Item(Key key, Data data, Item* right, Item* left, Item* parent, int consoleW)
{
	this->key = key;
	this->data = data;
	this->right = right;
	this->left = left;
	this->parent = parent;
	this->consoleW = consoleW;
}

template<typename Data, typename Key>
inline Tree<Data, Key>::Tree()
{

}

template<typename Data, typename Key>
inline Tree<Data, Key>::~Tree()
{
	clear(root);
}

template<typename Data, typename Key>
inline int Tree<Data, Key>::getSize()
{
	return size;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::clear(Item*& root)
{
	if (root) 
	{
		if (root->left) 
		{
			clear(root->left);
		}
		if (root->right) 
		{
			clear(root->right);
		}
		root = nullptr;
		size--;
	}
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::isEmpty()
{
	if (size > 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<typename Data, typename Key>
inline Data Tree<Data, Key>::read(Key key, Item*& root)
{
	if (root) 
	{
		viewedItems++;
		if (key == root->key) 
		{
			return root->data;
		}
		else if (key < root->key) 
		{
			read(key, root->left);
		}
		else if (key > root->key) 
		{
			read(key, root->right);
		}
	}
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::edit(Key key, Data newData, Item*& root)
{
	if (root) 
	{
		viewedItems++;
		if (key == root->key) 
		{
			root->data = newData;
		}
		else if (key < root->key) 
		{
			edit(key, newData, root->left);
		}
		else if (key > root->key) 
		{
			edit(key, newData, root->right);
		}
	}
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::add(Key key, Data data, Item*& root, Item*& parent)
{
	if (root) 
	{
		viewedItems++;
		if (key < root->key) 
		{
			add(key, data, root->left, root);
		}
		else if (key > root->key) 
		{
			add(key, data, root->right, root);
		}
	}
	else 
	{
		root = new Item(key, data);
		if (getSize() > 0) 
		{
			root->parent = parent;
		}
		size++;
	}
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::deleteItem(Key key, Item*& root)
{
	if (root) 
	{
		viewedItems++;
		if (key == root->key) 
		{
			root->data = 0;
			size--;
		}
		else if (key < root->key) 
		{
			deleteItem(key, root->left);
		}
		else if (key > root->key) 
		{
			deleteItem(key, root->right);
		}
	}
}

// ����������� �����
template<typename Data, typename Key>
inline void Tree<Data, Key>::printHorizontal(Item*& root, int indent)
{
	if (root) 
	{
		if (root->right) 
		{
			printHorizontal(root->right, indent + 4);
		}
		if (indent) 
		{
			std::cout << std::setw(indent) << ' ';
		}
		if (root->right) 
		{
			std::cout << " /\n" << std::setw(indent) << ' ';
		}
		std::cout << root->key << ":" << root->data << "\n ";
		if (root->left) 
		{
			std::cout << std::setw(indent) << ' ' << " \\\n";
			printHorizontal(root->left, indent + 4);
		}
	}
	else 
	{
		std::cout << "������ ������\n";
	}
}

// ����������� �����
template<typename Data, typename Key>
inline void Tree<Data, Key>::printVertical(Item*& root)
{
	if (root) 
	{
		int height = getTreeHeight(root);
		std::queue<Item*>* treeLevels = new std::queue<Item*>[height];
		// ���������� �������� �� �������
		for (int i = 1; i <= height; i++) 
		{
			std::stack<Item*> stack;
			stack.push(root);
			while (!stack.empty()) 
			{
				Item* current = stack.top();
				// ������ �������, �������� � ���� ��� ��������
				stack.pop();
				if (current->right) 
				{
					stack.push(current->right);
				}
				if (current->left) 
				{
					stack.push(current->left);
				}
				// ���� ������� ������� � ������� ������ ������
				if (getDepth(current) == i) 
				{
					treeLevels[i - 1].push(current);
				}
			}
		}
		// ����� ���� �������� � �������
		int step = 10;
		for (int i = 0; i < height; i++) 
		{
			bool first = true;
			while (!treeLevels[i].empty()) 
			{
				Item* current = treeLevels[i].front();
				int rNum = rand() % 3;
				int lenght;
				// ������ ������
				if (!current->parent) 
				{
					// �������� ����� �������
					current->consoleW = 50;
					std::cout << std::setw(current->consoleW);
				}
				// �����
				else if (current->parent->key > current->key) 
				{
					current->consoleW = current->parent->consoleW - (step + rNum);
					lenght = current->parent->consoleW;
					std::cout << std::setw(lenght) << "/\n";
					std::cout << std::setw(current->consoleW);
				}
				// ������
				else if (current->parent->key < current->key) 
				{
					current->consoleW = current->parent->consoleW + (step + rNum);
					lenght = current->consoleW;
					std::cout << std::setw(lenght) << "\\\n";
					std::cout << std::setw(current->consoleW);
				}
				std::cout << current->key << ':' << current->data << "\n";
				treeLevels[i].pop();
			}
		}
		delete[] treeLevels;
	}
	else 
	{
		std::cout << "������ ������\n";
	}
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::t_Lt_Rt(Item*& root)
{
	if (!root) 
	{
		return;
	}
	std::cout << root->key << " ";
	print_Lt_Rt_t(root->left);
	print_Lt_Rt_t(root->right);
}

template<typename Data, typename Key>
inline int Tree<Data, Key>::getTreeHeight(Item*& root)
{
	// ����������� �������� � ���������
	int h1 = 0, h2 = 0;
	if (!root) 
	{
		return 0;
	}
	if (root->left) 
	{
		h2 = getTreeHeight(root->left);
	}
	if (root->right) 
	{
		h1 = getTreeHeight(root->right);
	}
	return (std::max(h1, h2) + 1);
}

template<typename Data, typename Key>
inline int Tree<Data, Key>::getDepth(Item*& target)
{
	Item* current = target;
	int depth = 1;
	while (current != root) 
	{
		current = current->parent;
		depth++;
	}
	return depth;
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::isContain(Key key, Item*& root)
{
	while (root) 
	{
		if (key == root->key) 
		{
			return true;
		}
		else if (key < root->key) 
		{
			root = root->left;
		}
		else if (key > root->key) 
		{
			root = root->right;
		}
	}
	return false;
}

template<typename Data, typename Key>
inline int Tree<Data, Key>::getViewedItems()
{
	return viewedItems;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::print_Lt_Rt_t(Item*& root)
{
	if (!root) 
	{
		return;
	}
	print_Lt_Rt_t(root->left);
	print_Lt_Rt_t(root->right);
	std::cout << root->key << " ";
}

template<typename Data, typename Key>
inline Tree<Data, Key>::Iterator Tree<Data, Key>::begin()
{
	Iterator it;
	it.obj = root;
	return it;
}

template<typename Data, typename Key>
inline Tree<Data, Key>::Iterator Tree<Data, Key>::end()
{
	// ����������� �������� � ���������
	Iterator it;
	it.obj = nullptr;
	std::stack<Item*> stack;
	stack.push(root);
	while (!stack.empty()) 
	{
		Item* current = stack.top();
		it.obj = current;
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
	}
	return it;
}

template<typename Data, typename Key>
inline Tree<Data, Key>::Item* Tree<Data, Key>::lt_Rt_t(Item*& root)
{
	if (!root) 
	{
		return nullptr;
	}
	lt_Rt_t(root->left);
	lt_Rt_t(root->right);
	return root;
}

template<typename Data, typename Key>
inline Data& Tree<Data, Key>::Iterator::operator*()
{
	return this->obj->data;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::Iterator::operator++(int)
{
	Iterator it = *this;
	// ����������� � ����� ������
	while (it.obj->parent) 
	{
		it.obj = it.obj->parent;
	}
	std::stack<Item*> stack;
	// �������� ������ � ����
	stack.push(it.obj);
	while (!stack.empty()) 
	{
		// ����� �������� �������� �����
		Item* current = stack.top();
		// ������ �������, �������� � ���� ��� ��������
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
		// ���� ����� ��������, ����� ���������� �������� � �����
		if (current == this->obj && stack.size()) 
		{
			it.obj = stack.top();
			break;
		}
		else if (!stack.size()) 
		{
			std::cout << "����� �� �������!\n";
			return;
		}
	}
	*this = it;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::Iterator::operator--(int)
{
	Iterator it = *this;
	if (it.obj->parent == nullptr) 
	{
		std::cout << "����� �� �������!\n";
		return;
	}
	// ����������� � ����� ������
	while (it.obj->parent) 
	{
		it.obj = it.obj->parent;
	}
	std::stack<Item*> stack;
	// �������� ������ � ����
	stack.push(it.obj);
	while (!stack.empty()) 
	{
		// ����� �������� �������� �����
		Item* current = stack.top();
		// ������ �������, �������� � ���� ��� ��������
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
		// ���� ����� ��������, ����� ����������� (�����) �������� � �����
		if (stack.top() == this->obj) 
		{
			it.obj = current;
			break;
		}
	}
	*this = it;
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::Iterator::operator==(const Iterator& it)
{
	if (obj == it.obj) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::Iterator::operator!=(const Iterator& it)
{
	if (obj != it.obj)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<typename Data, typename Key>
inline Tree<Data, Key>::ReverseIterator Tree<Data, Key>::rBegin()
{
	// ����������� �������� � ���������
	ReverseIterator it;
	it.obj = nullptr;
	std::stack<Item*> stack;
	stack.push(root);
	while (!stack.empty()) 
	{
		Item* current = stack.top();
		it.obj = current;
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
	}
	return it;
}

template<typename Data, typename Key>
inline Tree<Data, Key>::ReverseIterator Tree<Data, Key>::rEnd()
{
	ReverseIterator it;
	it.obj = root;
	return it;
}

template<typename Data, typename Key>
inline Data& Tree<Data, Key>::ReverseIterator::operator*()
{
	return this->obj->data;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::ReverseIterator::operator++(int)
{
	ReverseIterator it = *this;
	if (it.obj->parent == nullptr) 
	{
		std::cout << "����� �� �������!\n";
		return;
	}
	// ����������� � ����� ������
	while (it.obj->parent) 
	{
		it.obj = it.obj->parent;
	}
	std::stack<Item*> stack;
	// �������� ������ � ����
	stack.push(it.obj);
	while (!stack.empty()) 
	{
		// ����� �������� �������� �����
		Item* current = stack.top();
		// ������ �������, �������� � ���� ��� ��������
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
		// ���� ����� ��������, ����� ����������� (�����) �������� � �����
		if (stack.top() == this->obj) 
		{
			it.obj = current;
			break;
		}
	}
	*this = it;
}

template<typename Data, typename Key>
inline void Tree<Data, Key>::ReverseIterator::operator--(int)
{
	ReverseIterator it = *this;
	// ����������� � ����� ������
	while (it.obj->parent) 
	{
		it.obj = it.obj->parent;
	}
	std::stack<Item*> stack;
	// �������� ������ � ����
	stack.push(it.obj);
	while (!stack.empty()) 
	{
		// ����� �������� �������� �����
		Item* current = stack.top();
		// ������ �������, �������� � ���� ��� ��������
		stack.pop();
		if (current->right) 
		{
			stack.push(current->right);
		}
		if (current->left) 
		{
			stack.push(current->left);
		}
		// ���� ����� ��������, ����� ���������� �������� � �����
		if (current == this->obj && stack.size()) 
		{
			it.obj = stack.top();
			break;
		}
		else if (!stack.size()) 
		{
			std::cout << "����� �� �������!\n";
			return;
		}
	}
	*this = it;
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::ReverseIterator::operator==(const ReverseIterator& it)
{
	if (obj == it.obj) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<typename Data, typename Key>
inline bool Tree<Data, Key>::ReverseIterator::operator!=(const ReverseIterator& it)
{
	if (obj != it.obj) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}