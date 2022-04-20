// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Helper functions

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

// Helper function to get the module base address
uintptr_t GetBaseAddress();

// Helper function to convert a pointer to hex
template<typename T> std::string to_hex_string(T i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
    return stream.str();
}

std::string translate_type_name(std::string input);
Il2CppMethodPointer find_method(Il2CppClass* klass, std::string returnType, std::string methodName, std::string paramTypes);
Il2CppMethodPointer get_method(std::string methodSignature);
Il2CppClass* get_class(std::string classSignature);
std::string get_method_description(const MethodInfo* methodInfo);
void output_class_methods(Il2CppClass* klass);
void output_assembly_methods(const Il2CppAssembly* assembly);