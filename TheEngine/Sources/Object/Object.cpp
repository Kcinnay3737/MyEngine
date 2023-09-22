#include "Object/Object.h"

using namespace NPEngine;

size_t Object::_CurrentID = 0;

Object::Object()
{
	_ID = GetNextID();
}

Object::~Object()
{

}

size_t NPEngine::Object::GetNextID()
{
	return Object::_CurrentID++;
}