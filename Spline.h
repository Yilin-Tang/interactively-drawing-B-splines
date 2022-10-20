#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

enum class SplineType { UNIFORM, QUASI_UNIFORM, CUSTOM };

class Spline
{
public:
	std::vector<glm::vec2> controls;
	std::vector<float> knots;
	std::vector<glm::vec2> points;
	std::vector<glm::vec2> knot_points;
	int degree;
	SplineType type;
	int sr = 200;  //sample rate

	glm::vec2 curvepoint(float t);
	void curvepoints();
	void add_control(glm::vec2 new_ctrl);

	void draw_spline(Shader& shader);
	void draw_control_polygon(Shader& shader);
	void draw_control_points(Shader& shader);
	void draw_knot_points(Shader& shader);

	void print_data();

	Spline(std::vector<glm::vec2>& c, std::vector<float>& u, int& k); //CUSTOM
	Spline(SplineType type, int degree) :type(type), degree(degree) { setup(); }

private:
	unsigned int VAO[4];
	unsigned int VBO[4]; //0:points  1:control_polygon  2:control_points  3:knot_points
	void gen_setup();
	void bind_setup();
	void setup();
	int findspan(float t);
	void gen_knots();
};

#endif