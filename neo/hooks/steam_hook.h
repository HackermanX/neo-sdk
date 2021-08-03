#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <iostream>
#include <memory>
#include <Psapi.h>
#include <chrono>
#include <thread>

#define declare_hook(name, type)                \
    struct name                                 \
    {                                           \
        using fn = std::remove_pointer_t<type>; \
        static fn hook;                         \
        static fn *original;                    \
    };                                          \
    inline name::fn *name::original;

namespace steam {
	template <typename T>
	void* hook(void* function) {
		auto addr_to_hook_func = utils::pattern_scan("gameoverlayrenderer.dll", "55 8B EC 51 8B 45 10 C7");

		typedef void* (__cdecl* proxy_function)(void*, void*, void*, int);
		proxy_function do_hook_fn = (proxy_function)addr_to_hook_func;

		return do_hook_fn(function, T::hook, &T::original, 0);
	} //thanks xemacs for making me realise that im a retard so i can make this not shit <3
}