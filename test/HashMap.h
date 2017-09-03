#pragma once
#include <iostream>
#include <string>
#include <vector>

template<typename Key, typename Value>
class HashMap
{
public:
	struct Node
	{
		Key key;
		Value value;
		Node* next = nullptr;
	};
	typedef std::vector<Node*>		NodePointerVector;
	typedef const Key&				constKeyRef;
	typedef const Value&			constValueRef;
	typedef HashMap&&				RhashMap;
	typedef const HashMap&			constMapRef;
private:
	int size;											/*size of the vector*/
	NodePointerVector *vec;								/*pointer of vector*/
public:
	HashMap(int _size = 100);							/*defauwlt constructor*/
	HashMap(constMapRef map);							/*copy constructor*/
	HashMap(RhashMap map);								/*move constructor*/
	~HashMap();											/*destructor*/
	bool insert(constKeyRef key, constValueRef value);	/*insert a pair*/
	bool remove(constKeyRef key);						/*remove a pair*/
	bool find(constKeyRef key, constValueRef value);	/*return if the pair is in map*/
	Value getValue(constKeyRef key);					/*use key to get value*/
private:
	bool isBucketEmpty(int index);						/*return if the bucket is empty*/
	void deleteAll();									/*delete all the nodes*/
private:
	int hash(const int& key);							/*use int to get hash value*/
	int hash(const double& key);						/*use double to get hash value*/
	int hash(const unsigned int& key);					/*use unsigned int to get hash value*/
	int hash(const char& key);							/*use char to get hash value*/
	int hash(const char* key);							/*use char* to get hash value*/
	int hash(const std::string& key);					/*use std::string to get hash value*/
};
#pragma region HashMap functions
/*****************************
  constructor and destructor
******************************/
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(int _size) : size(_size)
{
	vec = new std::vector<Node*>();						/*allocate memory*/
	for (int i = 0; i < size; i++)						/*initilizate vector*/
	{
		Node* p = nullptr;
		vec->push_back(p);
	}
}
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(RhashMap map)
{
	size = map.size;			
	vec = map.vec;										/*move vector*/
	map.vec = nullptr;
}
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(constMapRef map)
{
	HashMap(map.size);									

	//TODO
}
template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
	deleteAll();
	delete vec;
}
/*****************************
	operation functions
*****************************/
template<typename Key, typename Value>
bool HashMap<Key, Value>::insert(constKeyRef key, constValueRef value)
{
	int index = hash(key);
	if (isBucketEmpty(index))							/*if the bucket is empty, new a node*/
	{
		/****** old function ********

		Node** p = &(vec->at(index));
		*p = new Node();
		(*p)->value = value;
		(*p)->key = key;

		*****************************/
		vec->at(index) = new Node();						
		auto p = vec->at(index);
		p->value = value;
		p->key = key;
		p->next = nullptr;
		return true;
	}
	else                                                /*if the bucket is no empty*/
	{
		if (!find(key, value))							/*if the bucket doesnt have the same pair, new a node*/
		{
			auto p = vec->at(index);
			while (p != nullptr)
				p = p->next;
			p = new Node();
			p->value = value;
			p->key = key;
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
template<typename Key, typename Value>
bool HashMap<Key, Value>::remove(constKeyRef key)
{
	int index = hash(key);
	if (isBucketEmpty(index))
	{
		return false;
	}
	auto current = &vec->at(index);
	Node* temp;
	while ((*current) != nullptr)
	{
		if ((*current)->key == key)
		{
			temp = (*current)->next;
			delete *current;
			*current = temp;
			return true;
		}
		*current = (*current)->next;
	}
	return false;
}
template<typename Key, typename Value>
bool HashMap<Key, Value>::isBucketEmpty(int index)
{
	auto p = vec->at(index);
	if (p == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
template<typename Key, typename Value>
bool HashMap<Key, Value>::find(constKeyRef key, constValueRef value)
{
	int index = hash(key);
	Node* temp = vec->at(index);
	while (temp != nullptr)
	{
		if (temp->value == value)
			return true;
		temp = temp->next;
	}
	return false;
}
template<typename Key, typename Value>
Value HashMap<Key, Value>::getValue(constKeyRef key)
{
	int index = hash(key);
	if (isBucketEmpty(index))
	{
		return NULL;
	}
	else
	{
		auto p = vec->at(index);
		while (p != nullptr)
		{
			if (p->key == key)
				return p->value;
			p = p->next;
		}
	}
}
/*****************************
		hash functions
******************************/
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const int& key)
{
	return abs(key) % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const unsigned int& key)
{
	return key % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const double& key)
{
	return abs((int)key) % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const char& key)
{
	return (unsigned int)key % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const char* key)
{
	const char* p = key;
	unsigned int sum = 0;
	while (*p != '\0')
		sum += (unsigned int)*p++;
	return sum % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const std::string& key)
{
	unsigned int sum = 0;
	for (auto ch : key)
	{
		sum += (unsigned int)ch;
	}
	return sum % size;
}
template<typename Key, typename Value>
void HashMap<Key, Value>::deleteAll()
{
	for (int i = 0; i < vec->size(); i++)
	{
		if (isBucketEmpty(i))
		{
			continue;
		}
		else
		{
			auto current = vec->at(i);
			Node* temp;
			while (current != nullptr)
			{
				temp = current->next;
				delete current;
				current = temp;
			}
		}
	}
}
#pragma endregion