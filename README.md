# Digital FOV
## Symetrical 2D FOV for tile-based games

[Image demo 1](https://i.sli.mg/mH3V6S.png)

[Image demo 2](https://i.sli.mg/ObAX5M.png)

[Image demo 3](https://i.sli.mg/iTNH4Y.png)

[Animated gif demo](https://i.sli.mg/ish0PS.gif)

### How it works
Digital FOV works by using digital lines to check if line-of-sight exists between two points. Using a modified version of Brensenham's line algorithm, Digital FOV checks all possible digital lines between two points and if any unobstructed lines exist, there is line-of-sight.

### How to use it
To use Digital FOV, you can either use the `los` method to determine if line-of-sight exists between two points or you can construct an `fov` object to get a map of all the visible points on a map from a single point. Both of these methods require a `map2<bool, width, height>` as an input. A `map2` is just a fixed-size 2D array with a 2D `at` method which takes an `x` and a `y`. The line-of-sight method is declared as `bool los(map2<bool, width, height> opacity, std::size_t x0, std::size_t y0, std::size_t x1, std::size_t y1)`. `opacity` is the opacity map. In the opacity map, `true` is opaque, `false` is transparent. `x0` and `y0` are one point, and `x1` and `y1` are a second point. The method returns true if line-of-sight exists between the two points. The field-of-vision constructor is declared as `fov(map2<bool, width, height> opacity, std::size_t x, std::size_t y)`. Again, `opacity` is your opacity map, and `x` and `y` are the point you want to get the field-of-vision from. `fov` inheirits from `map2<bool, width, height>` and you can use the `at(std::size_t x, std::size_t y)` method to access points on the `fov` map. *Example code below.*
```
// Create a 50 by 50 opacity map
map2<bool, 50, 50> opacity;

// Populate the map with whatever you want however you want using opacity.at(x, y)
...

// Create an fov map from the opacity map using 31, 17 a the vantage point
fov<50, 50> my_field_of_vision(opacity, 31, 17);

// Check if the point at 22, 11 is visible (from 31, 17)
if(field_of_vision.at(22, 11)){
    // It's visible!
}
```
