#pragma once
#include "../classes/client_class.h"
#include "i_app_system.h"
#include "global_vars.h"
#include <cstdint>

enum class frame_stage {
    UNDEFINED = -1,
    START,
    NET_UPDATE_START,
    NET_UPDATE_POSTDATAUPDATE_START,
    NET_UPDATE_POSTDATAUPDATE_END,
    NET_UPDATE_END,
    RENDER_START,
    RENDER_END
};

class i_base_client_dll {
public:
    virtual int              connect(create_interface_fn appSystemFactory, c_global_vars_base* pGlobals) = 0;
    virtual int              disconnect(void) = 0;
    virtual int              init(create_interface_fn appSystemFactory, c_global_vars_base* pGlobals) = 0;
    virtual void             post_init() = 0;
    virtual void             shutdown(void) = 0;
    virtual void             level_init_pre_entity(char const* pMapName) = 0;
    virtual void             level_init_post_entity() = 0;
    virtual void             level_shutdown(void) = 0;
    virtual client_class*    get_client_classes(void) = 0;

    bool dispatch_user_msg(int type, uint32_t a3, uint32_t len, void* data) {
        using original_fn = bool(__thiscall*)(i_base_client_dll*, int, uint32_t, uint32_t, void*);
        return (*(original_fn**)this)[38](this, type, a3, len, data);
    }
};