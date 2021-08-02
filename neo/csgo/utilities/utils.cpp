#include "utils.h"

HANDLE _out = NULL, _old_out = NULL;
HANDLE _err = NULL, _old_err = NULL;
HANDLE _in = NULL, _old_in = NULL;

namespace utils {
#define FIND_NT_HEADER(x) reinterpret_cast<PIMAGE_NT_HEADERS>( uint32_t(x) + reinterpret_cast<PIMAGE_DOS_HEADER>(x)->e_lfanew )
	uint8_t* pattern_scan(const char* module_name, const std::string_view signature) {
		std::vector<uint8_t> signature_bytes{ }; {
			signature_bytes.resize(signature.size());
			std::vector<std::string> signature_chunks{ };
			std::string current_chunk{ };
			std::istringstream string_stream{ signature.data() };
			while (std::getline(string_stream, current_chunk, ' '))
				signature_chunks.push_back(current_chunk);
			std::transform(signature_chunks.cbegin(), signature_chunks.cend(), signature_bytes.begin(), [](const std::string& val) -> uint8_t{
					return val.find('?') != std::string::npos ? 0ui8 : static_cast<uint8_t>(std::stoi(val, nullptr, 16)); });
		}
		uint8_t* found_bytes = nullptr; {
			const auto image_start = reinterpret_cast<uint8_t*>(GetModuleHandleA(module_name));
			const auto image_end = image_start + FIND_NT_HEADER(image_start)->OptionalHeader.SizeOfImage;
			const auto result = std::search(image_start, image_end, signature_bytes.cbegin(), signature_bytes.cend(), [](uint8_t left, uint8_t right) -> bool {
					return right == 0ui8 || left == right; });
			found_bytes = (result != image_end) ? result : nullptr;
		} return found_bytes;
	}
    void attach_console() {
        _old_out = GetStdHandle(STD_OUTPUT_HANDLE);
        _old_err = GetStdHandle(STD_ERROR_HANDLE);
        _old_in = GetStdHandle(STD_INPUT_HANDLE);
        ::AllocConsole() && ::AttachConsole(GetCurrentProcessId());
        _out = GetStdHandle(STD_OUTPUT_HANDLE);
        _err = GetStdHandle(STD_ERROR_HANDLE);
        _in = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(_out,
            ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
        SetConsoleMode(_in,
            ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
            ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
    }
    void detach_console() {
        if (_out && _err && _in) {
            FreeConsole();
            if (_old_out)
                SetStdHandle(STD_OUTPUT_HANDLE, _old_out);
            if (_old_err)
                SetStdHandle(STD_ERROR_HANDLE, _old_err);
            if (_old_in)
                SetStdHandle(STD_INPUT_HANDLE, _old_in);
        }
    }
    bool console_print(const char* fmt, ...) {
        if (!_out)
            return false;
        char buf[1024];
        va_list va;
        va_start(va, fmt);
        _vsnprintf_s(buf, 1024, fmt, va);
        va_end(va);
        return !!WriteConsoleA(_out, buf, static_cast<DWORD>(strlen(buf)), nullptr, nullptr);
    }
    void* create_interface(const char* module_name, const char* iface_name) {
        using create_interface_fn = void* (*)(const char*, void*);
        auto fn_addr = (create_interface_fn)GetProcAddress(GetModuleHandleA(module_name), "CreateInterface");
        auto iface_addr = fn_addr(iface_name, nullptr);
        printf("[+] found %s at 0x%p\n", iface_name, iface_addr);
        return iface_addr;
    }
    ImU32 to_im32(const color& color, const float& alpha)
    {
        return ImGui::GetColorU32(ImVec4(color.r() / 255.f, color.g() / 255.f, color.b() / 255.f, alpha));
    }
}