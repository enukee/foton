#pragma once

#include "MyForm.h"
#include <regex>

using namespace prog3v3;
using namespace System::Runtime::InteropServices;

boolean is_integer(System::Object^ sender) {
	boolean flag = 0;

	char* text = (char*)Marshal::StringToHGlobalAnsi((safe_cast<TextBox^>(sender))->Text).ToPointer();
	std::regex r("(-?)(\\d)+");

	if (std::regex_match(text, r)) {
		flag = 1;
	}

	return flag;
}

// проверка, чсло входит в интервал чисел 
void checking_the_value(System::Object^ sender, int max) {
	int value = Int32::Parse((safe_cast<TextBox^>(sender))->Text);
	if (value < 0) {
		(safe_cast<TextBox^>(sender))->Text = "0";
	}
	if (value >= max) {
		(safe_cast<TextBox^>(sender))->Text = System::Convert::ToString(max);
	}
}
