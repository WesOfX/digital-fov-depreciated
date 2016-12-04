#pragma once

#include <array>
#include <algorithm>

template<typename element_type, std::size_t width, std::size_t height>
// A 2D array with a 2D access method
class map2{
public:
	// Returns an element using a 2D index
	element_type& at(std::size_t x, std::size_t y){
		return elements.at(y * width + x);
	}
private:
	// An array representing a 2D array
	std::array<element_type, width * height> elements;
};
