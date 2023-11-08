#include "Player/Issac.h"
#include "Engine.h"

Isaac::Isaac(std::string& Name) : Player(Name)
{

}

Actor* Isaac::Clone(std::string& Name, const Param& Params)
{
	Isaac* CopyIsaac = new Isaac(Name);
	return CopyIsaac;
}