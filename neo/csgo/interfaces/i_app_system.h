#pragma once
typedef void* (*create_interface_fn)(const char* pName, int* pReturnCode);
typedef void* (*instantiate_interface_fn)();

class i_app_system
{
public:
    virtual bool                            connect(create_interface_fn factory) = 0;                                     
    virtual void                            disconnect() = 0;                                                          
    virtual void*                           query_interface(const char* pInterfaceName) = 0;                            
    virtual int /*InitReturnVal_t*/         init() = 0;                                                                
    virtual void                            shutdown() = 0;                                                            
    virtual const void* /*AppSystemInfo_t*/ get_dependencies() = 0;
    virtual int /*AppSystemTier_t*/         get_tier() = 0;                                                              
    virtual void                            reconnect(create_interface_fn factory, const char* pInterfaceName) = 0;     
    virtual void                            unk_func() = 0;                                                             
};