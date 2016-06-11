#include <type_traits>
#include <typeinfo>

#ifndef _MSC_VER
#include <cxxabi.h>
#endif

#include <memory>
#include <string>
#include <cstdlib>
#include <iostream>

template<typename T>
std::string type_name(){
	using TR = typename std::remove_reference<T>;
	std::unique_ptr<char, void(*)(void*)> own(
	#ifndef __GNU__
		nullptr,
	#else
		abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
	#endif
		std::free
	);
	std::string r = own ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)r += " const";
	if (std::is_volatile<TR>::value)r += " volatile";
	if (std::is_lvalue_reference<TR>::value)r += "&";
	else if (std::is_rvalue_reference<TR>::value)r += "&&";
	return r;
}

template<typename T>
void Func(T&& t){
	std::cout << type_name<T>() << std::endl;
}

// 测试代码
void TestReference(){
	std::string str = "test";
	Func(str);
	Func(std::move(str));
}
