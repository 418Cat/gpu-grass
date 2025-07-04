#ifndef UI_H
#define UI_H

#include "ui_errors.h"

#include <iostream>

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class UI
{

	public:
		static bool show_ui;
		static GLFWwindow* window;
		static ImGuiIO* io;
		static float clear_color[4];

	private:
		static bool is_init;
		static bool render_started;


	public: static UI_ERROR 	ui_init();
			static UI_ERROR 	ui_render_start();
			static UI_ERROR 	ui_render_stop();	
			static UI_ERROR 	ui_cleanup();
			static bool 		ui_is_shown();
			static GLFWwindow* 	get_window();
			static UI_ERROR 	get_win_size(int* x, int* y); 
	
	
	static void glfw_error_callback(int error, const char* description)
	{
		std::cerr
			<< "GLFW Error code: " << error
			<< "\nGLFW Error: " << description
			<< std::endl;
	}

};


#endif
