# Interactively Drawing B-splines
This program is used to draw a 2D B-spline curve interactively by clicking control points. The interface will show the spline in green, the control polygon and points in yellow and the knot points in blue.

## Usage
You can change the type (``UNIFORM`` or ``QUASI_UNIFORM``) and the degree of the spline in ``main.cpp``. You can also customize the knots, control points and degree of the B-spline curve with the type ``CUSTOM`` in ``main.cpp``, as long as they satisfy ``knots.size() = degree + control_points.size() + 1``.

The code has to be compiled in **Release** mode.

## Demo
![demo](https://s3.us-west-2.amazonaws.com/secure.notion-static.com/6a2de517-c685-4d17-823f-36e9be7df27c/Untitled.png?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Content-Sha256=UNSIGNED-PAYLOAD&X-Amz-Credential=AKIAT73L2G45EIPT3X45%2F20221208%2Fus-west-2%2Fs3%2Faws4_request&X-Amz-Date=20221208T111653Z&X-Amz-Expires=86400&X-Amz-Signature=3ad513631969e4ac44ba4e66db0db317892f48f0b8d481189327dd7e48887be9&X-Amz-SignedHeaders=host&response-content-disposition=filename%3D%22Untitled.png%22&x-id=GetObject)