#pragma once 
#include "i_client_networkable.h"
#include "i_client_renderable.h"
#include "i_client_unknown.h"
#include "i_client_thinkable.h"

struct spatialization_info_t;

class i_client_entity : public i_client_unknown, public i_client_renderable, public i_client_networkable, public i_client_thinkable
{
public:
	virtual void release(void) = 0;
};