#include "HashMap.h"

HashMap::HashMap(int _size) : size(_size)
{
	vec = new std::vector<Node*>();
	for (int i = 0; i < size; i++)
	{
		Node* p = nullptr;
		vec->push_back(p);
	}
}
HashMap::~HashMap()
{
	deleteAll();
	delete vec;
}
bool HashMap::insert(int key, std::string value)
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
bool HashMap::remove(int key)
{
	return true;
}
bool HashMap::isBucketEmpty(int index)
{
	auto p = vec->at(index);
	if (p == nullptr)
		return true;
	else
		return false;
}
bool HashMap::find(int index, std::string value)
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
std::string HashMap::getValue(int key)
{
	int index = hash(key);
	if (isBucketEmpty(index))
	{
		std::cout << "get empty\n";
		return "";
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
int HashMap::hash(int key)
{
	return abs(key) % size;
}
void HashMap::deleteAll()
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