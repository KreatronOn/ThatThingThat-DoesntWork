#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;

#include"Chunk.h"
#include"Collision.h"
#include"Placing.h"
#include"Speed.h"
#include"Camera.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


const unsigned int width = 1920;
const unsigned int height = 1080;

//GLfloat block[] = {
//	0.0f,	0.0f,	0.0f,		0.0f,	0.0f,		0.0f, -1.0f, 0.0f, //y-
//	0.0f,	0.0f,	1.0f,		1.0f,	0.0f,		0.0f, -1.0f, 0.0f,
//	1.0f,	0.0f,	0.0f,		0.0f,	1.0f,		0.0f, -1.0f, 0.0f,
//	1.0f,	0.0f,	1.0f,		1.0f,	1.0f,		0.0f, -1.0f, 0.0f,
//
//	0.0f,	0.0f,	0.0f,		0.0f,	0.0f,		-1.0f, 0.0f, 0.0f,//x-
//	0.0f,	0.0f,	1.0f,		0.0f,	1.0f,		-1.0f, 0.0f, 0.0f,
//	0.0f,	1.0f,	0.0f,		1.0f,	0.0f,		-1.0f, 0.0f, 0.0f,
//	0.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		-1.0f, 0.0f, 0.0f,
//
//	0.0f, 	0.0f,	0.0f,		0.0f,	0.0f,		0.0f, 0.0f, -1.0f,//z-
//	0.0f,	1.0f,	0.0f,		0.0f,	1.0f,		0.0f, 0.0f, -1.0f,
//	1.0f,	0.0f,	0.0f,		1.0f,	0.0f,		0.0f, 0.0f, -1.0f,
//	1.0f,	1.0f,	0.0f,		1.0f,	1.0f,		0.0f, 0.0f, -1.0f,
//
//	0.0f,	1.0f,	0.0f,		0.0f,	0.0f,		0.0f, 1.0f, 0.0f,//y+
//	0.0f,	1.0f,	1.0f,		1.0f,	0.0f,		0.0f, 1.0f, 0.0f,
//	1.0f,	1.0f,	0.0f,		0.0f,	1.0f,		0.0f, 1.0f, 0.0f,
//	1.0f,	1.0f,	1.0f,		1.0f,	1.0f,		0.0f, 1.0f, 0.0f,
//
//	1.0f,	0.0f,	0.0f,		0.0f,	0.0f,		1.0f, 0.0f, 0.0f,//x+
//	1.0f,	0.0f,	1.0f,		0.0f,	1.0f,		1.0f, 0.0f, 0.0f,
//	1.0f,	1.0f,	0.0f,		1.0f,	0.0f,		1.0f, 0.0f, 0.0f,
//	1.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		1.0f, 0.0f, 0.0f,
//
//	0.0f,	0.0f,	1.0f,		0.0f,	0.0f,		0.0f, 0.0f, 1.0f,//z+
//	1.0f,	0.0f,	1.0f,		1.0f,	0.0f,		0.0f, 0.0f, 1.0f,
//	0.0f,	1.0f,	1.0f,		0.0f,	1.0f,		0.0f, 0.0f, 1.0f,
//	1.0f, 	1.0f,	1.0f,		1.0f,	1.0f,		0.0f, 0.0f, 1.0f
//};
//
//GLuint iBlock[] = {
//	0, 2, 1,		//y-
//	1, 2, 3,
//
//	4, 5, 6,		//x-
//	5, 7, 6,
//
//	9, 10, 8,		//z-
//	11, 10, 9,
//
//	12, 13, 14,		//y+
//	13, 15, 14,
//
//	16, 18, 17,		//x+
//	17, 18, 19,
//
//	20, 21, 22,		//z+
//	21, 23, 22, 
//};

vector<glm::vec3> lightVertices = {
	glm::vec3(-0.1f, -0.1f,	 0.1f),
	glm::vec3(-0.1f, -0.1f,	-0.1f),
	glm::vec3(0.1f,  -0.1f,	-0.1f),
	glm::vec3(0.1f,  -0.1f,	 0.1f),
	glm::vec3(-0.1f, 0.1f,	 0.1f),
	glm::vec3(-0.1f, 0.1f,	-0.1f),
	glm::vec3(0.1f,  0.1f,	-0.1f),
	glm::vec3(0.1f,	 0.1f,	 0.1f)
};

vector<int> lightIndices = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7

};

void renderUI(GLFWwindow* window) {

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Your UI code goes here
	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	// Center the square in the middle of the screen
	ImVec2 squareSize((screenSize.x / screenSize.y) * 5.0f, (screenSize.y / screenSize.y) * 5.0f);
	ImVec2 squarePos((screenSize.x - squareSize.x) * 0.5f, (screenSize.y - squareSize.y) * 0.5f);

	// Draw a white square in the center
	ImGui::SetNextWindowPos(squarePos);
	ImGui::SetNextWindowSize(squareSize);
	ImGui::Begin("White Square", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs);

	// Change the square color to white
	ImGui::GetWindowDrawList()->AddRectFilled(squarePos, ImVec2(squarePos.x + squareSize.x, squarePos.y + squareSize.y), IM_COL32(0, 0, 0, 100));

	ImGui::End();

	// Render UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


int main()
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glfwInit();	// Initialize GLFW


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// Tell GLFW what version of OpenGL we are using 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Tell GLFW we are using the CORE profile

	GLFWwindow* window = glfwCreateWindow(width, height, "ForestCraft", NULL, NULL); // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	if (window == NULL)		// Error check if the window fails to create
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);		// Introduce the window into the current context
	gladLoadGL();	//Load GLAD so it configures OpenGL
	glViewport(0, 0, width, height);	// Specify the viewport of OpenGL in the Window

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int word[16][64][16];

	//vector <int> blocks;
	//for (int i = 0; i < 2147365765; i++){
	//	blocks.push_back(i);
	//}

	//ofstream create;
	//create.open("save.txt");
	//for (int x = 0; x < size(word); x++) {
	//	for (int y = 0; y < size(word[x]); y++) {
	//		for (int z = 0; z < size(word[x][y]); z++) {
	//			if (y == 31) {
	//				create << x << "," << y << "," << z << "," << 2 << "," << endl;
	//			}
	//			if (y < 31 and y > 31) {
	//				create << x << "," << y << "," << z << "," << 1 << "," << endl;
	//			}
	//		}
	//	}
	//}
	//create.close();

	vector <string> save;
	fstream file;
	file.open("save.txt");
	string chr;
	while (!file.eof()) {
		file >> chr;
		save.push_back(chr);
	}
	file.close();

	vector <vector <int>> world;
	string mhm;
	for (int i = 0; i < size(save); i++) {
		world.push_back(vector <int>());
		//cout << endl;
		int a = 0;
		int b = 0;

		for (int j = 0; j < save[i].size(); j++) {
			if (save[i][j] == ',') {
				mhm = save[i];
				string h = string(mhm.substr(j - a, a));
				world[i].push_back(stoi(h));
				//cout << h << " | ";
				a = 0;
				b++;
			}
			else {
				a++;
			}
		}
	}

	for (int x = 0; x < size(word); x++) {
		for (int y = 0; y < size(word[x]); y++) {
			for (int z = 0; z < size(word[x][y]); z++) {
				word[x][y][z] = 0;
			}
		}
	}

	for (int i = 0; i < size(world); i++) {
		word[(world[i][0])][(world[i][1])][(world[i][2])] = world[i][3];
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Shader shaderProgram("chunk.vert", "chunk.frag");

	Shader lightShader("light.vert", "light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices);
	EBO lightEBO(lightIndices);
	lightVAO.LinkAttrib(0, 3, lightVBO);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(1.5f, 1.0f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	lightShader.Bind();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	glEnable(GL_DEPTH_TEST);	//so the vertecies dont go over each other
	//glEnable(GL_CULL_FACE);		//so that i dont render back of the blocks from my prerspective

	Camera camera(width, height, glm::vec3(0.0f, 0.5f, 0.0f));	//creating camera object
	Placing placing;
	Collision collision;

	Chunk chunk(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));
	shaderProgram.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	float start;
	float frameTime;
	float desiredFPSms = 1 / 200.0f;
	float waitMs;

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	float prevTime = 0.0f;
	float crntTime;
	float timeDelta;
	unsigned int counter = 0;

	while (!glfwWindowShouldClose(window)){
		start = glfwGetTime();

		crntTime = glfwGetTime();
		timeDelta = crntTime - prevTime;
		counter++;
		float FPS = (1.0f / timeDelta) * counter;
		float ms = (timeDelta / counter) * 1000;
		if (timeDelta >= 1.0/ 10.0) {
			string title = "ForestCraf - " + to_string(FPS) + "FPS / " + std::to_string(ms) + "ms";
			glfwSetWindowTitle(window, title.c_str());
			prevTime = crntTime;
			counter = 0;
		}
		Speed gameSpeed(FPS, ms / 1000);

		camera.cameraSpeedApply(ms/1000);
	///////////////////////////////////////////////////////////////////////////////////////////////////////


		glClearColor(0.52f, 0.8f, 0.92f, 1.0f);	//background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clean the back buffer and assign the new color to it

		camera.updateMatrix(70.0f, 0.01f, 10000.0f);	//fov, start clip, end clip, shader, uniform for shader
		
		shaderProgram.Bind();
		//glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		chunk.Render(shaderProgram);


		renderUI(window);

		placing.Click(word, window, camera);

		collision.Collisions(camera, window, word);
		
		lightShader.Bind();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);					// Swap the back buffer with the front buffer
		glfwPollEvents();							// Take care of all GLFW events

		frameTime = glfwGetTime() - start;
		waitMs = glfwGetTime() + desiredFPSms - frameTime;
		while (waitMs > glfwGetTime()) {

		}
	}

	shaderProgram.Delete();
	//blockVAO.Delete();
	//blockVBO.Delete();
	//blockEBO.Delete();
	//
	//grassTex.Delete();
	//cobTex.Delete();

	chunk.Delete();

	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);	// Delete window before ending the program
	glfwTerminate();	// Terminate GLFW before ending the program
	return 0;
}
