#pragma once

#include "handle_entity.h"
#include "i_colideable.h"

class i_client_networkable;
class i_client_renderable;
class i_client_entity;
class entity_t;
class IClientThinkable;
class IClientAlphaProperty;

class i_client_unknown : public i_handle_entity
{
public:
    virtual i_colideable* get_collideable() = 0;
    virtual i_client_networkable* GetClientNetworkable() = 0;
    virtual i_client_renderable* GetClientRenderable() = 0;
    virtual i_client_entity* GetIClientEntity() = 0;
    virtual entity_t* GetBaseEntity() = 0;
    virtual IClientThinkable* GetClientThinkable() = 0;
    //virtual IClientModelRenderable*  GetClientModelRenderable() = 0;
    virtual IClientAlphaProperty* GetClientAlphaProperty() = 0;
};