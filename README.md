# Interactively Drawing B-splines
This program is used to draw a 2D B-spline curve interactively by clicking control points. The interface will show the spline in green, the control polygon and points in yellow and the knot points in blue.

## Usage
You can change the type (``UNIFORM`` or ``QUASI_UNIFORM``) and the degree of the spline in ``main.cpp``. You can also customize the knots, control points and degree of the B-spline curve with the type ``CUSTOM`` in ``main.cpp``, as long as they satisfy ``knots.size() = degree + control_points.size() + 1``.

The code has to be compiled in **Release** mode.

## Demo
![demo-Bspline.png](https://i.postimg.cc/SQvPsx7s/demo-Bspline.png)