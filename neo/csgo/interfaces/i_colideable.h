#pragma once
#include "../math/vector_3d.h"

enum SolidType_t;
class IHandleEntity;
struct Ray_t;
struct model_t;
class CGameTrace;
typedef CGameTrace trace_t;
class IClientUnknown;
class matrix3x4_t;

class i_colideable
{
public:
    virtual IHandleEntity* GetEntityHandle() = 0;
    virtual const vec3_t& obb_mins() const = 0;
    virtual const vec3_t& obb_maxs() const = 0;
    virtual void                WorldSpaceTriggerBounds(vec3_t* pVecWorldMins, vec3_t* pVecWorldMaxs) const = 0;
    virtual bool                TestCollision(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
    virtual bool                TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, trace_t& tr) = 0;
    virtual int                 GetCollisionModelIndex() = 0;
    virtual const model_t* GetCollisionModel() = 0;
    virtual const vec3_t& GetCollisionOrigin() const = 0;
    virtual const vec3_t& GetCollisionAngles() const = 0;
    virtual const matrix3x4_t& CollisionToWorldTransform() const = 0;
    virtual SolidType_t         GetSolid() const = 0;
    virtual int                 GetSolidFlags() const = 0;
    virtual IClientUnknown* GetIClientUnknown() = 0;
    virtual int                 GetCollisionGroup() const = 0;
    virtual void                WorldSpaceSurroundingBounds(vec3_t* pVecMins, vec3_t* pVecMaxs) = 0;
    virtual bool                ShouldTouchTrigger(int triggerSolidFlags) const = 0;
    virtual const matrix3x4_t* GetRootParentToWorldTransform() const = 0;
};