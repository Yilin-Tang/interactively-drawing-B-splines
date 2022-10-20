//A simple program for drawing 3 kinds of B-spline with glut

#include <vector>
#include <glm/glm.hpp>
#include <gl/glut.h>

const unsigned int SCR_width = 1000;
const unsigned int SCR_height = 1000;

int findspan(float t,std::vector<float> knots)
{
    int j = 0;
    while (knots[j] <= t)
        j++;
    return j - 1;
}

glm::vec2 curvepoint(float t, std::vector<glm::vec2> controls, std::vector<float> knots,int degree)
{
    int j = findspan(t,knots);
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

void draw()
{
    //data for bezier curve
    /*std::vector<glm::vec2> controls;
    controls.push_back(glm::vec2(-0.5f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.5f));
    controls.push_back(glm::vec2(0.25f, 0.5f));
    controls.push_back(glm::vec2(0.5f, 0.0f));
    std::vector<float> knots{ 0, 0, 0, 0, 1, 1, 1, 1 };
    float degree = 3;*/

    //data for clamped, uniform B-spline curve: 7 controls and degree 3
    /*std::vector<glm::vec2> controls;
    controls.push_back(glm::vec2(-0.75f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.5f));
    controls.push_back(glm::vec2(0.25f, 0.5f));
    controls.push_back(glm::vec2(0.45f, 0.0f));
    controls.push_back(glm::vec2(0.1f, -0.25f));
    controls.push_back(glm::vec2(-0.25f, -0.1f));
    std::vector<float> knots{ 0, 0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1, 1 };
    float degree = 3;*/

    //data for clamped, uniform B-spline curve: 6 controls and degree 3
    //std::vector<glm::vec2> controls;
    //controls.push_back(glm::vec2(-0.75f, 0.0f));
    //controls.push_back(glm::vec2(-0.25f, 0.0f));
    //controls.push_back(glm::vec2(-0.25f, 0.5f));
    //controls.push_back(glm::vec2(0.25f, 0.5f));
    //controls.push_back(glm::vec2(0.45f, 0.0f));
    //controls.push_back(glm::vec2(0.1f, -0.25f));
    ////controls.push_back(glm::vec2(-0.25f, -0.1f));
    //std::vector<float> knots{ 0, 0, 0, 0, 1.0f/3, 2.0f/3, 1, 1, 1, 1 };
    //float degree = 3;

    //data for unclamped, uniform B-spline curve: 7 controls nad degree 3
    std::vector<glm::vec2> controls;
    controls.push_back(glm::vec2(-0.75f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.5f));
    controls.push_back(glm::vec2(0.25f, 0.5f));
    controls.push_back(glm::vec2(0.45f, 0.0f));
    controls.push_back(glm::vec2(0.1f, -0.25f));
    controls.push_back(glm::vec2(-0.25f, -0.1f));
    std::vector<float> knots{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float degree = 3;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_STRIP); //control polygon
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    for (int i = 0; i < controls.size(); i++)
        glVertex2f(controls[i].x, controls[i].y);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_STRIP); //B-spline curve
    glLineWidth(3.0f);
    glm::vec2 temp;
    for (float t = knots[degree]; t < knots[knots.size()-1-degree]; t += 0.01) //×¢Òâ²ÎÊý·¶Î§£¡
    {
        temp = curvepoint(t, controls, knots, degree);
        glVertex2f(temp.x, temp.y);
    }
    glEnd();

    //glColor3f(1.0f, 0.0f, 0.0f);
    //glBegin(GL_LINE_STRIP); //knots
    //glPointSize(50.0f);
    //for (int i = 0; i < knots.size(); i++)
    //{
    //    if (knots[i] < 1)
    //    {
    //        temp = curvepoint(knots[i], controls, knots, degree);
    //        glVertex2f(temp.x, temp.y);
    //    }
    //}
    //glEnd();

    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutCreateWindow("B spline curve");
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}