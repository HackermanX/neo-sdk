#pragma once
#include "../classes/studio.h"

class CPhysCollide;
class CUtlBuffer;
class IClientRenderable;
class CStudioHdr;
struct virtualmodel_t;
class vcollide_t;
class IMaterial;
class constvec3_t;
class CGameTrace;
typedef CGameTrace trace_t;

enum RenderableTranslucencyType_t
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,    // has both translucent and opaque sub-partsa
};

class iv_model_info
{
public:
	virtual                                 ~iv_model_info(void) {}
	virtual const model_t* GetModel(int modelindex) const = 0;
	virtual int                             GetModelIndex(const char* name) const = 0;
	virtual const char* GetModelName(const model_t* model) const = 0;
	virtual vcollide_t* GetVCollide(const model_t* model) const = 0;
	virtual vcollide_t* GetVCollide(int modelindex) const = 0;
	virtual void                            GetModelBounds(const model_t* model,vec3_t& mins,vec3_t& maxs) const = 0;
	virtual void                            GetModelRenderBounds(const model_t* model,vec3_t& mins,vec3_t& maxs) const = 0;
	virtual int                             GetModelFrameCount(const model_t* model) const = 0;
	virtual int                             GetModelType(const model_t* model) const = 0;
	virtual void* GetModelExtraData(const model_t* model) = 0;
	virtual bool                            ModelHasMaterialProxy(const model_t* model) const = 0;
	virtual bool                            IsTranslucent(model_t const* model) const = 0;
	virtual bool                            IsTranslucentTwoPass(const model_t* model) const = 0;
	virtual void                            Unused0() {};
	virtual void UNUSED() = 0;
	virtual void UNUSE11D() = 0;
	virtual RenderableTranslucencyType_t    ComputeTranslucencyType(const model_t* model, int nSkin, int nBody) = 0;
	virtual int                             GetModelMaterialCount(const model_t* model) const = 0;
	virtual void                            GetModelMaterials(const model_t* model, int count, IMaterial** ppMaterial) = 0;
	virtual bool                            IsModelVertexLit(const model_t* model) const = 0;
	virtual const char* GetModelKeyValueText(const model_t* model) = 0;
	virtual bool                            GetModelKeyValue(const model_t* model, CUtlBuffer& buf) = 0;
	virtual float                           GetModelRadius(const model_t* model) = 0;
	virtual CStudioHdr* GetStudioHdr(MDLHandle_t handle) = 0;
	virtual const studiohdr_t* FindModel(const studiohdr_t* pStudioHdr, void** cache, const char* modelname) const = 0;
	virtual const studiohdr_t* FindModel(void* cache) const = 0;
	virtual virtualmodel_t* GetVirtualModel(const studiohdr_t* pStudioHdr) const = 0;
	virtual uint8_t* GetAnimBlock(const studiohdr_t* pStudioHdr, int iBlock) const = 0;
	virtual void                            GetModelMaterialColorAndLighting(const model_t* model,vec3_t const& origin, vec3_t const& angles, trace_t* pTrace,vec3_t& lighting,vec3_t& matColor) = 0;
	virtual void                            GetIlluminationPoint(const model_t* model, IClientRenderable* pRenderable,vec3_t const& origin, vec3_t const& angles,vec3_t* pLightingCenter) = 0;
	virtual int                             GetModelContents(int modelIndex) const = 0;
	virtual studiohdr_t* get_studio_model(const model_t* mod) = 0;
	virtual int                             GetModelSpriteWidth(const model_t* model) const = 0;
	virtual int                             GetModelSpriteHeight(const model_t* model) const = 0;
	virtual void                            SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void                            GetLevelScreenFadeRange(float* pMinArea, float* pMaxArea) const = 0;
	virtual void                            SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual unsigned char                   ComputeLevelScreenFade(constvec3_t& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char                   ComputeViewScreenFade(constvec3_t& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual int                             GetAutoplayList(const studiohdr_t* pStudioHdr, unsigned short** pAutoplayList) const = 0;
	virtual CPhysCollide* GetCollideForVirtualTerrain(int index) = 0;
	virtual bool                            IsUsingFBTexture(const model_t* model, int nSkin, int nBody, IClientRenderable** pClientRenderable) const = 0;
	virtual const model_t* FindOrLoadModel(const char* name) const = 0;
	virtual MDLHandle_t                     GetCacheHandle(const model_t* model) const = 0;
	virtual int                             GetBrushModelPlaneCount(const model_t* model) const = 0;
	virtual void                            GetBrushModelPlane(const model_t* model, int nIndex, cplane_t& plane,vec3_t* pOrigin) const = 0;
	virtual int                             GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual bool                            UsesEnvCubemap(const model_t* model) const = 0;
	virtual bool                            UsesStaticLighting(const model_t* model) const = 0;
};

class iv_model_info_client : public iv_model_info
{
public:
};