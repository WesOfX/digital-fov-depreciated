#pragma once

#include <array>

#include "map2.hpp"
#include "digital_line.hpp"

namespace dfov{
template<std::size_t width, std::size_t height>
class field_of_vision: public map2<bool, width, height>{
public:
	// Construct a field-of-vision map using an opacity map and a position
	constexpr field_of_vision(map2<bool, width, height> opacity, std::size_t x, std::size_t y){
		// For every point on the field-of-vision map
		for(std::size_t collum = 0; collum < width; collum++){
			for(std::size_t row = 0; row < height; row++){
				field_of_vision::at(collum, row) = los(opacity, x, y, collum, row);
			}
		}
	}

	/* Returns true if an unobstructed line-of-sight exists
	 * between the two points on the opacity map */
	static constexpr bool los(
		map2<bool, width, height> opacity,
		std::size_t x0,
		std::size_t y0,
		std::size_t x1,
		std::size_t y1
	){
		// The offset of the two points
		long int x_offset = x1 - x0,
		         y_offset = y1 - y0;

		// The properties of the digital line
		std::size_t word_length = std::max(abs(x_offset), abs(y_offset)),
		            diagonal_count = std::min(abs(x_offset), abs(y_offset));

		// For every unique digital line between the two points
		for(std::size_t eps = 0; eps < word_length; eps++){
			// The digital line
			auto line = digital_line<std::max(width, height)>(word_length, diagonal_count, eps);

			// The point being checked
			auto x = x0, y = y0;

			// Whether the line is clear or not (false until proven true)
			bool obstructed = false;

			// For all but the last point on the digital line
			for(std::size_t i = 0; i < word_length; i++){
				/* If any point along the line is opaque,
				 * the line is not clear */
				if(opacity.at(x, y)){
					obstructed = true;
					break;
				}

				/* Determine the octant to update x and y
				 * TODO This should probably be optimized because every
				 * point on a line is in the same octant, yet it's checked
				 * for every point here */
				if(x_offset > 0){ // East
					if(y_offset > 0){ // Southeast
						if(x_offset > y_offset){ // Southeast-east
							x++;
							if(line.at(i)) y++;
						}
						else{ // South-southeast
							y++;
							if(line.at(i)) x++;
						}
					}
					else{ // Northeast
						if(x_offset > abs(y_offset)){ // Northeast-east
							x++;
							if(line.at(i)) y--;
						}
						else{ // North-northeast
							y--;
							if(line.at(i)) x++;
						}
					}
				}
				else{ // West
					if(y_offset > 0){ // Southwest
						if(abs(x_offset) > y_offset){ // Southwest-west
							x--;
							if(line.at(i)) y++;
						}
						else{ // South-southwest
							y++;
							if(line.at(i)) x--;
						}
					}
					else{ // Northwest
						if(abs(x_offset) > abs(y_offset)){ // Northwest-west
							x--;
							if(line.at(i)) y--;
						}
						else{ // North-northwest
							y--;
							if(line.at(i)) x--;
						}
					}
				}
			}

			// If any line is clear, there is line-of-sight
			if(!obstructed) return true;
		}

		// If no clear lines exist, there is no line-of-sight
		return false;
	}
};
};
