#include "HashMap.h"

HashMap::HashMap(int _size) : size(_size)
{
	vec = new std::vector<Node*>();
	for (int i = 0; i < size; i++)
		vec->push_back(new Node());
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
	if (p->value == "")
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
			auto p = vec->at(i);
			delete p;
			p = nullptr;
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