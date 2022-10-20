#include "glfw_utils.cpp"
#include "Spline.h"
#include "Shader.h"

const unsigned int SCR_width = 1000;
const unsigned int SCR_height = 1000;

bool isClick = false;
double xcursor;
double ycursor;

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //if left button is pressed
    {
        isClick = true;
        glfwGetCursorPos(window, &xcursor, &ycursor);
        xcursor = (xcursor / SCR_width) * 2 - 1;
        ycursor = -((ycursor / SCR_height) * 2 - 1);
    }
}

int main()
{
    glfwInitial();
    GLFWwindow* window = CreateWindow(SCR_width, SCR_height, "B-Spline Curve");

    /*std::vector<glm::vec2> controls;
    controls.push_back(glm::vec2(-0.5f, 0.0f));
    controls.push_back(glm::vec2(-0.25f, 0.5f));
    controls.push_back(glm::vec2(0.25f, 0.5f));
    controls.push_back(glm::vec2(0.5f, 0.0f));
    std::vector<float> knots{ 0, 0, 0, 0, 1, 1, 1, 1 };
    int degree = 3;
    Spline spline(controls, knots, degree);*/

    int degree = 3;
    SplineType type = SplineType::QUASI_UNIFORM;
    Spline spline(type, degree);

    // Shaders
    Shader shader_spline("vertex_shader.vs", "fragment_shader.fs");
    shader_spline.use();
    shader_spline.setVec3("color", glm::vec3(0.2f, 0.9f, 0.2f)); // green

    Shader shader_control_polygon("vertex_shader.vs", "fragment_shader.fs");
    shader_control_polygon.use();
    shader_control_polygon.setVec3("color", glm::vec3(0.8f, 0.6f, 0.0f)); // yellow

    Shader shader_control_points("vertex_shader.vs", "fragment_shader.fs");
    shader_control_points.use();
    shader_control_points.setVec3("color", glm::vec3(1.0f, 0.8f, 0.0f)); // yellow

    Shader shader_knot_points("vertex_shader.vs", "fragment_shader.fs");
    shader_knot_points.use();
    shader_knot_points.setVec3("color", glm::vec3(0.55f, 0.6f, 0.8f)); // blue

    // Process Click Event
    glfwSetMouseButtonCallback(window, mouse_callback);

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);  // background color
        glClear(GL_COLOR_BUFFER_BIT);
        if (isClick)
        {
            spline.add_control(glm::vec2(xcursor, ycursor));
            spline.print_data();
            isClick = false;
        }
        spline.draw_spline(shader_spline);
        spline.draw_control_polygon(shader_control_polygon);
        spline.draw_control_points(shader_control_points);
        spline.draw_knot_points(shader_knot_points);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}