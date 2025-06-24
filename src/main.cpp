#include <geometric.hpp>
#include <trigonometric.hpp>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <imgui.h>
#include <glad.c>


#include "shader.h"
#include "ui.h"
#include "Camera.h"

void create_plane(unsigned int vbo, unsigned int ebo)
{
	float vertices[] = 
	{
	 //  X    Y     Z      U    V
		 1.f, 0.f,  1.f,   1.f, 1.f,
		-1.f, 0.f,  1.f,   0.f, 1.f,
		-1.f, 0.f, -1.f,   0.f, 0.f,
		 1.f, 0.f, -1.f,   1.f, 0.f,
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

std::string get_root_dir(char* file_path)
{
	std::string fpath = std::string(file_path);
	std::string dpath = fpath.substr(0, fpath.find_last_of("/")+1); // Unix only
	return dpath;
}

int main(int a, char** args)
{

	UI::ui_init();
	UI::show_ui = true;
	UI::io->FontGlobalScale = 1.f;
	UI::io->IniFilename = NULL; // Disable imgui.ini file
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Setting up buffers and adding the plane
	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	create_plane(vbo, ebo);

	// Getting the shader files path relative to the main exec and compiling them
	std::string exec_dir = get_root_dir(args[0]);
	std::string vs_path = exec_dir + std::string("shaders/vs.glsl");
	std::string fs_path = exec_dir + std::string("shaders/fs.glsl");

	Shader shader = Shader(vs_path.c_str(), fs_path.c_str());
	shader.use();


	Camera camera = Camera(glm::vec3(-2.5f, 1.5f, -1.f));
	camera.turn_pitch(glm::radians(-50.));

	int win_width, win_height;
	UI::get_win_size(&win_width, &win_height);
	glm::mat4 projection_mat = glm::perspective(glm::radians(90.f), (float)win_width/(float)win_height, .1f, 100.f);
	glm::mat4 view_mat = camera.camera_space();

	float grass_height = .25f;	//
	int n_shells = 40;			// Number of planes stacked 
	float density = 60.;		//
	float plane_scale = 2.f;    // Length for the side of the plane

	float wind_direction = 1.f; // -pi < direction < pi
	float wind_curve = 2.f;  	// Exponent of grass height
	float wind_force = .07f; 	// How much the wind pushes on the grass
	float wind_speed = 1.8f; 	// How fast the wind speed oscillates


	float mouse_sensitivity = 1./100.;
	glm::vec2 mouse_pos = glm::vec2(UI::io->MousePos.x, UI::io->MousePos.y);
	glm::vec2 old_mouse_pos = mouse_pos;

	double time = 0.;

	while(UI::ui_is_shown())
	{
		double delta_time = glfwGetTime() - time;
		time = glfwGetTime();
		UI::ui_render_start();

		// Update the projection matrix with new window sizes
		UI::get_win_size(&win_width, &win_height);
		projection_mat = glm::perspective(glm::radians(90.f), (float)win_width/(float)win_height, .1f, 100.f);		

		/*
		 * ---------------------------------------------------------------------
		 *  UI Stuff 
		 * ---------------------------------------------------------------------
		 */
		ImGui::Text("Plane settings");
		ImGui::DragFloat("Plane size", &plane_scale, plane_scale*0.05);
		ImGui::SliderInt("Number of shells", &n_shells, 1, 600);

		ImGui::Spacing(); ImGui::Text("Grass settings");
		ImGui::DragFloat("Grass density", &density);
		ImGui::SliderFloat("Grass Height", &grass_height, 0.01f, 2.f);

		ImGui::Spacing(); ImGui::Text("Wind settings");
		ImGui::SliderFloat("Wind direction", &wind_direction, -3.1415, 3.1415f);
		ImGui::SliderFloat("Wind curve", &wind_curve, 0.01f, 10.f);
		ImGui::SliderFloat("Wind force", &wind_force, 0.0f, .5f);
		ImGui::SliderFloat("Wind speed", &wind_speed, 0.f, 4.f);

		ImGui::Spacing();
		if(ImGui::Button("Reset view"))
		{
			camera.camera_pos = glm::vec3(0.);

			// Cancel the camera's orientation
			camera.turn_pitch(-camera.get_pitch());
			camera.turn_yaw(-camera.get_yaw());
		}


		/*
		 * ---------------------------------------------------------------------
		 *  Camera movement & rotation
		 * ---------------------------------------------------------------------
		 */
		mouse_pos = glm::vec2(UI::io->MousePos.x, UI::io->MousePos.y);
		glm::vec2 delta_mouse = mouse_pos - old_mouse_pos;
		old_mouse_pos = mouse_pos;
		
		// If lmb and mouse not used by imgui
		if(		glfwGetMouseButton(UI::window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
				!UI::io->WantCaptureMouse)
		{
			camera.turn_yaw(delta_mouse.x*mouse_sensitivity);
			camera.turn_pitch(-delta_mouse.y*mouse_sensitivity);
		}

		// My keyboard layout is AZERTY but for some reason glfw doesn't care
		if(glfwGetKey(UI::window, GLFW_KEY_W) == GLFW_PRESS)
		{
			// Add camera front vector to its position
			camera.camera_pos += camera.get_front()*(float)delta_time;
		}
		if(glfwGetKey(UI::window, GLFW_KEY_D) == GLFW_PRESS)
		{
			// Cross product with world Y to get right facing vector
			camera.camera_pos +=
				glm::normalize(glm::cross(camera.get_front(), glm::vec3(0.f, 1.f, 0.f)))*(float)delta_time;
		}
		if(glfwGetKey(UI::window, GLFW_KEY_A) == GLFW_PRESS)
		{
			// Negated cross product with world Y to get left facing vector
			camera.camera_pos += 
				-glm::normalize(glm::cross(camera.get_front(), glm::vec3(0.f, 1.f, 0.f)))*(float)delta_time;
		}
		if(glfwGetKey(UI::window, GLFW_KEY_S) == GLFW_PRESS)
		{
			// Substract front facing vector to camera pos
			camera.camera_pos += -camera.get_front()*(float)delta_time;
		}

		view_mat = camera.camera_space(); // Update view matrix


		/*
		 * ---------------------------------------------------------------------
		 *  Drawing planes
		 * ---------------------------------------------------------------------
		 */
		glm::mat4 model_mat = glm::mat4(1.f);

		// Setting uniforms
		shader.setMat4("model", glm::value_ptr(model_mat));
		shader.setMat4("view", glm::value_ptr(view_mat));
		shader.setMat4("projection", glm::value_ptr(projection_mat));

		shader.setInt("n_squares", density*plane_scale);
		shader.setInt("n_shells", n_shells);

		shader.setFloat("total_height", grass_height);
		shader.setFloat("wind_direction", wind_direction);
		shader.setFloat("wind_curve", wind_curve);
		shader.setFloat("wind_force", wind_force/plane_scale);
		shader.setFloat("wind_speed", wind_speed);
		shader.setFloat("time", glfwGetTime());

		// Draw n_shells instances of planes
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, n_shells);

		UI::ui_render_stop();
	}

	UI::ui_cleanup();
	return 0;
}
