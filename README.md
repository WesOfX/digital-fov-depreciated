# Digital FOV
## Digital-line field-of-vision for 2D tile-based games

[Image demo 1](https://i.sli.mg/mH3V6S.png)

[Image demo 2](https://i.sli.mg/ObAX5M.png)

[Image demo 3](https://i.sli.mg/iTNH4Y.png)

[Animated gif demo](https://i.sli.mg/ish0PS.gif)

### How it works
Digital FOV works by using digital lines to check if line-of-sight exists between two points. Using a modified version of Brensenham's line algorithm, Digital FOV checks all possible digital lines between two points and if any unobstructed lines exist, there is line-of-sight.

### How to use it
To use Digital FOV, you can either use the `line_of_sight` method to determine if line-of-sight exists between two points or you can construct an `field_of_vision` object to get a map of all the visible points on a map from a single point. Both methods require a `map2<bool, width, height>` as an input. A `map2` is just a fixed-size 2D array with a 2D `at` method which takes an `x` and a `y`. The `line_of_sight` method returns true if line-of-sight exists between the two points and it is used inside the `field_of_vision` constructor. *Example code below.*
```
// Create a 50 by 50 opacity map
map2<bool, 50, 50> opacity;

// Populate the map with whatever you want however you want using opacity.at(x, y)
...

// Create an fov map from the opacity map using 31, 17 a the vantage point
dfov::field_of_vision<50, 50> my_fov(opacity, 31, 17);

// Check if 22, 11 is visible (from 31, 17)
if(my_fov.at(22, 11)){
    // It's visible!
}
```
