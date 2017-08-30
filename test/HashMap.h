#pragma once
#include <iostream>
#include <string>
#include <vector>

class HashMap
{
public:
	struct Node
	{
		int key = -1;
		std::string value = "";
		Node* next = nullptr;
	};
	typedef std::vector<Node*>	NodeVector;
private:
	int size;
	NodeVector *vec;
public:
	HashMap(int _size = 100);
	~HashMap();
	bool insert(int key, std::string value);
	bool remove(int key);
	bool isBucketEmpty(int index);
	bool find(int index, std::string value);
	std::string getValue(int key);
private:
	int hash(int key);
	void deleteAll();
};
