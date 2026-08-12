// testcmake.cpp : Defines the entry point for the application.
//

#include "main.h"

/*#include "imgui/imgui.h"
#include "implot/implot.h"

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
*/
#include <GLFW/glfw3.h>
//#include "glfw/include/GLFW/glfw3.h"

using namespace std;

int main()
{
	GLFWwindow* window;
	if( !glfwInit() ) { return -1; }

	window = glfwCreateWindow(640, 480, "Application", NULL, NULL);
	if( !window ) { glfwTerminate(); return -1; }

	glfwMakeContextCurrent(window);

	while( !glfwWindowShouldClose(window) )
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
