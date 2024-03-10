#include "ECS.h"

void Entity::AddGroup(Group ip_sGroup)
{
	voGroupBitset[ip_sGroup] = true;
	manager.AddToGroup(this, ip_sGroup);
}