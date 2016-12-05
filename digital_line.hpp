#pragma once

#include <array>

/* A digital line is a boolear array where false is lateral
 * and true is diagonal
 * maximum_length determins the size of the internal array */
namespace dfov{
template<std::size_t maximum_length>
class digital_line{
	/* The boolean array to represent the digital line's path
	 * false is lateral and true is diagonal */
	std::array<bool, maximum_length> path;
public:
	/* Creates a digital line
	 * Using a different eps gives you a different line
	 * The number of unique lines that exist is equal to word_length */
	constexpr digital_line(
		std::size_t word_length, // The number of booleans in the word
		std::size_t diagonal_count, // The number of trues in the word
		std::size_t eps = 0 /* Every eps from 0 to word_length - 1
							   gives you a different, but valid line */
	){
		// Brensenham's line algorithm
		for(std::size_t i = 0; i < word_length; i++){
			eps += diagonal_count;
			if(eps >= word_length){ // Diagonal
				eps -= word_length;
				path[i] = true;
			}
			else{ // Lateral
				path[i] = false;
			}
		}
	}

	// Return a boolean from the line
	auto& at(std::size_t i){
		return path.at(i);
	}
};
};
