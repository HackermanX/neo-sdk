#pragma once
#include "minhook.h"
class detour_hook {
public:
	detour_hook() = default;
	explicit detour_hook(void* function, void* detour)
		: base_fn(function), replace_fn(detour) { }
	~detour_hook(){
		this->remove();
	}
	bool create(void* function, void* detour) {
		base_fn = function;
		if (base_fn == nullptr)
			return false;
		replace_fn = detour;
		if (replace_fn == nullptr)
			return false;
		MH_STATUS status = MH_CreateHook(base_fn, replace_fn, &original_fn);
		if (status == MH_OK) {
			if (!this->replace())
				return false;
		}else {
			return false;
		}return true;
	}
	bool replace() {
		if (base_fn == nullptr)
			return false;
		if (is_hooked_fn)
			return false;
		MH_STATUS status = MH_EnableHook(base_fn);
		if (status == MH_OK)
			is_hooked_fn = true;
		else {
			return false;
		} return true;
	}
	bool remove() {
		if (!this->restore())
			return false;
		MH_STATUS status = MH_RemoveHook(base_fn);
		if (status == MH_OK)
			return true;
		else {
			return false;
		} return false;
	}
	bool restore() {
		if (!is_hooked_fn)
			return false;
		MH_STATUS status = MH_DisableHook(base_fn);
		if (status == MH_OK)
			is_hooked_fn = false;
		else{
			return false;
		}return true;
	}
	template <typename Fn>
	Fn get_original() {
		return (Fn)original_fn;
	}
	inline bool is_hooked() {
		return is_hooked_fn;
	}
private:
	bool is_hooked_fn = false;
	void* base_fn = nullptr;
	void* replace_fn = nullptr;
	void* original_fn = nullptr;
};