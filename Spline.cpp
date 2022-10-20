#include "Spline.h"
#include <stdio.h>

Spline::Spline(std::vector<glm::vec2>& c, std::vector<float>& u, int& k)
{
	controls = c;
	knots = u;
	degree = k;
	type = SplineType::CUSTOM;
	curvepoints();
	setup();
}

int Spline::findspan(float t)
{	
	int j = 0;
	while (knots[j] <= t)
		j++;
	return j - 1;
}

glm::vec2 Spline::curvepoint(float t)
{
	int j = findspan(t);
	float tau;
	std::vector<glm::vec2> P = controls;
	for (int r = 1; r <= degree; r++)
		for (int i = j; i >= j - degree + r; i--) //calculate from back 
		{
			tau = (t - knots[i]) / (knots[i + degree - r + 1] - knots[i]);
			P[i] = tau * P[i] + (1 - tau) * P[i - 1];
		}
	return P[j];
}

void Spline::gen_knots()
{
	int num_knots = degree + controls.size() + 1;
	int n = num_knots - 2 * (degree + 1) + 1;
	switch (type)
	{
	case SplineType::UNIFORM:
		knots.clear();
		knots.reserve(num_knots);
		for (float i = 0; i < num_knots; i++)
			knots.push_back(i / num_knots);
		break;
	case SplineType::QUASI_UNIFORM:
		knots.clear();
		knots.reserve(num_knots);
		knots.insert(knots.begin(), degree + 1, 0.0f);
		for (float i = 1; i < n; i++)
			knots.push_back(i / n);
		knots.insert(knots.end(), degree + 1, 1.0f);
		break;
	default:
		if (knots.size() != num_knots) // check the size
			throw "the relationship among knots, control points and degree is wrong!\n";
		break;
	}
}


void Spline::curvepoints()
{
	gen_knots();
	points.clear();
	knot_points.clear();

	for (float t = knots[degree]; t < knots[knots.size() - 1 - degree]; t += 1.0f / sr)
		points.push_back(curvepoint(t));

	for (int i = degree; i < knots.size() - 1 - degree; i++)
		knot_points.push_back(curvepoint(knots[i]));
}

void Spline::add_control(glm::vec2 new_ctrl)
{
	if (type == SplineType::CUSTOM)
		return;
	else
	{
		controls.push_back(new_ctrl);
		if(controls.size() > degree) //at least k+1 control points are needed for calculating a k-degree spline
			curvepoints();
		bind_setup();
	}
}

void Spline::draw_spline(Shader& shader)
{
	shader.use();
	glBindVertexArray(VAO[0]);
	glLineWidth(5.0f);
	glDrawArrays(GL_LINE_STRIP, 0, points.size());
}

void Spline::draw_control_polygon(Shader& shader)
{
	shader.use();
	glBindVertexArray(VAO[1]);
	glLineWidth(2.5f);
	glDrawArrays(GL_LINE_STRIP, 0, controls.size());
}

void Spline::draw_control_points(Shader& shader)
{
	shader.use();
	glBindVertexArray(VAO[2]);
	glPointSize(15.0f);
	glDrawArrays(GL_POINTS, 0, controls.size());
}

void Spline::draw_knot_points(Shader& shader)
{
	shader.use();
	glBindVertexArray(VAO[3]);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 0, knot_points.size());
}

void Spline::gen_setup()
{
	glGenVertexArrays(4, VAO);
	glGenBuffers(4, VBO);
}

void Spline::bind_setup()
{
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec2), &points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(glm::vec2), &controls[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, controls.size() * sizeof(glm::vec2), &controls[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glBindVertexArray(VAO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, knot_points.size() * sizeof(glm::vec2), &knot_points[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
}

void Spline::setup()
{
	gen_setup();
	bind_setup();
}

void Spline::print_data()
{
	// degree
	printf("degree: %d\n", degree);

	// controls
	printf("controls: ");
	for (int i = 0; i < controls.size(); i++)
		printf("(%.3f, %.3f)    ", controls[i].x, controls[i].y);
	printf("\n");

	// knots
	printf("knots: ");
	for (int i = 0; i < knots.size(); i++)
		printf("%.3f  ", knots[i]);
	printf("\n\n");

}