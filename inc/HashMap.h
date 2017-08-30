#pragma once
#include <iostream>
#include <string>
#include <vector>

class HashMap
{
	struct Node
	{
		int key = -1;
		std::string value = "";
		Node* next = nullptr;
	};
private:
	int size;
	std::vector<Node*> *vec;
public:
	HashMap(int _size = 100);
	~HashMap();
	bool insert(int key, std::string value);
	bool remove(int key);
	bool isBucketEmpty(int index);
	bool find(int index, std::string value);
	std::string getValue(int key);
	void deleteAll();
private:
	int hash(int key);
};
