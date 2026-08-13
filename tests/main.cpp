// testcmake.cpp : Defines the entry point for the application.
//

#include "main.h"


#include "imgui.h"
#include "implot.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>


//#include "glfw/include/GLFW/glfw3.h"

int main()
{
	GLFWwindow* pGLFWwindow;
	if( !glfwInit() ) { return -1; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	pGLFWwindow = glfwCreateWindow(640, 480, "Application", NULL, NULL);
	if( !pGLFWwindow ) { glfwTerminate(); return -1; }

	// Initialize
	glfwMakeContextCurrent(pGLFWwindow);

	// Imgui -----------
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(pGLFWwindow, true);
	ImGui_ImplOpenGL3_Init("#version 120");

	// -----------------

	float triangleColor[4] = { 1.0f, 0.0f, 0.0f };

	while( !glfwWindowShouldClose(pGLFWwindow) )
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// DRAW HERE

		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Triangle");
		ImGui::ColorEdit3("Triangle Color", triangleColor);
		ImGui::End();

		// OpenGL
		glColor3f(
			triangleColor[0],
			triangleColor[1],
			triangleColor[2]
		);

		glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.0f, 0.5f);
		glEnd();

		// ---------

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(pGLFWwindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
