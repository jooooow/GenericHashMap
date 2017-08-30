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
	typedef std::vector<Node*>	NodeVector;
private:
	int size;
	NodeVector *vec;
public:
	HashMap(int _size = 100);
	~HashMap();
	bool insert(Key key, Value value);
	bool remove(Key key);
	bool isBucketEmpty(int index);
	bool find(int index, Value value);
	Value getValue(Key key);
private:
	//int hash(Key key);
	int hash(const int& key);
	int hash(const char& key);
	int hash(const char* key);
	int hash(const unsigned int& key);
	int hash(const std::string& key);
	void deleteAll();
};

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(int _size) : size(_size)
{
	vec = new std::vector<Node*>();
	for (int i = 0; i < size; i++)
	{
		Node* p = nullptr;
		vec->push_back(p);
	}
}

template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
	deleteAll();
	delete vec;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::insert(Key key, Value value)
{
	int index = hash(key);
	if (isBucketEmpty(index))
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
		return true;
	}
	else
	{
		if (!find(index, value))
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
bool HashMap<Key, Value>::remove(Key key)
{
	//TODO

	return true;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::isBucketEmpty(int index)
{
	auto p = vec->at(index);
	if (p == nullptr)
		return true;
	else
		return false;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::find(int index, Value value)
{
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
Value HashMap<Key, Value>::getValue(Key key)
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

//template<typename Key, typename Value>
//int HashMap<Key, Value>::hash(Key key)
//{
//	if (typeid(key) == typeid(int))
//	{
//		hash(key);
//	}
//	else if (typeid(key) == typeid(char))
//	{
//		return (int)key % size;
//	}
//	else
//	{
//		return 0;
//	}
//}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const int& key)
{
	return abs(key) % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const char& key)
{
	return (int)key % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const char* key)
{
	const char* p = key;
	int sum = 0;
	while (*p != '\0')
		sum += (int)*p++;
	return sum % size;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const unsigned int& key)
{
	return 0;
}
template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const std::string& key)
{
	return 0;
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
