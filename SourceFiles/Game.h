#pragma once

#ifndef GAME
#define GAME
#define _CRT_SECURE_NO_WARNINGS
#include"libs.h"


//ENUMERATION
enum shader_enum {
	SHADER_CORE_PROGRAM, SHADER_SUBDIV_PROGRAM
};

enum texture_enum {
	WATER, SAND, DIRT, GRASS, HILL, MOUNTAIN, SNOW
};

enum material_enum {
	MAT_1
};

enum mesh_enum {
	MESH_QUAD, MESH_PLANE
};

struct planeStr
{
	int numVertices;
	Vertex* vertices;

	int numIndices;
	GLuint* indices;
};

//for perlin noise
int dimension = 40;
float nrOctaves = 6.0f; //1-6
float frequency = 1.0;
float amplitude = 0.5; 
float water = 1.f;
float mountain = 1.f;
float fallout = 0.665;
float elevationSize = 0.0;
int mode = 0;

glm::vec2 ld = glm::vec2(2.0f, 1.0f);
glm::vec2 ru = glm::vec2(4.0f, 3.0f);

glm::vec3 hitVertex;
std::vector<glm::vec3> selectionVec;
bool stopDimension = false;
bool perlin = false;
bool generation = true;
bool stop = true;
int veciniSize = 1;
bool startModeDrawing = false;
int viewMode = 0;
int wireMode = 0;
static bool showWindow = true;
bool distroy = true;
int texMode = 1;
std::pair <int, std::vector<double>> pairFunc;
bool importVar = false;



void makePlaneVertices(planeStr& ret)
{
	//std::cout << dimension << std::endl;
	ret.numVertices = dimension * dimension;

	int half = dimension / 2;

	ret.vertices = new Vertex[dimension * dimension];

	for(int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
		{
			ret.vertices[i * dimension + j].position.x = j - half;
			ret.vertices[i * dimension + j].position.z = i - half;
			ret.vertices[i * dimension + j].position.y = 0;
			//std::cout << glm::to_string(ret.vertices[i * dimension + j].position) << std::endl << std::endl;
			//ret.vertices[i * dimension + j].color = glm::vec3(1, rand() / (float)RAND_MAX,rand() / (float)RAND_MAX);
			//ret.vertices[i * dimension + j].color = glm::vec3(1.f, 0.f, 0.f);
			ret.vertices[i * dimension + j].texcoord.x = (j - half);
			ret.vertices[i * dimension + j].texcoord.y = (i - half);
			ret.vertices[i * dimension + j].normal = glm::vec3(0.f, 0.f, 1.f);
		}
	
	//ret.vertices[1].position.y = 0.5;
	//for (int i = 0; i < dimension * dimension; i++)
	//{
	//	std::cout << ret.vertices[i].position.x << " "
	//	 << ret.vertices[i].position.y << " "
	//	 << ret.vertices[i].position.z << ""
	//	 << "\n";
	//}
	
}

void makePlaneIndices(planeStr& ret)
{
	ret.numIndices = (dimension - 1) * (dimension - 1) * 2 * 3; //2 traingles per square,3 indices per triangle
	ret.indices = new GLuint[ret.numIndices];

	int aux = 0;
	for(int row = 0; row < dimension - 1; row++)
		for (int col = 0; col < dimension - 1; col++)
		{
			ret.indices[aux++] = dimension * row + col;
			ret.indices[aux++] = dimension * row + col + dimension;
			ret.indices[aux++] = dimension * row + col + dimension + 1;

			ret.indices[aux++] = dimension * row + col;
			ret.indices[aux++] = dimension * row + col + dimension + 1;;
			ret.indices[aux++] = dimension * row + col + 1;
		}

	if (aux != ret.numIndices)
	{
		std::cout << "ERROR::BAD_NUM_OF_INDICES" << std::endl;
	}

}


void setHeightMap(planeStr& ret)
{
	PerlinNoise *pn = new PerlinNoise(dimension, nrOctaves, frequency, amplitude, fallout, ld, ru);
	noise::utils::NoiseMap hm = pn->getHeightMap();


	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
		{
			ret.vertices[i * dimension + j].position.y = hm.GetValue(i, j) * 3;

			//setam culori
			if (ret.vertices[i * dimension + j].position.y >= -20.0f && ret.vertices[i*dimension+j].position.y <= -4.25f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(70 / 255.f, 95 / 255.f, 115 / 255.f);
			}
			else if (ret.vertices[i * dimension + j].position.y >= -4.25f && ret.vertices[i*dimension + j].position.y <= -2.25f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(73 / 255.f, 92 / 255.f, 39 / 255.f);
			}
			else if (ret.vertices[i*dimension+j].position.y > -2.25f && ret.vertices[i*dimension+j].position.y <= -1.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(20 / 255.f, 128 / 255.f, 20 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > -1.f && ret.vertices[i*dimension + j].position.y <= 0.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(124 / 255.f, 145 / 255.f, 76 / 255.f);
			}
			else if (ret.vertices[i*dimension+j].position.y > 0.f && ret.vertices[i*dimension+j].position.y <= 0.6625f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(94.f / 255.f, 128 / 255.f, 51 / 255.f);
			}
			else if (ret.vertices[i*dimension+j].position.y > 0.6625f && ret.vertices[i*dimension+j].position.y <= 1.1250)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(75 / 255.f, 92 / 255.f, 64 / 255.f);
			}
			else if (ret.vertices[i*dimension+j].position.y > 1.1250 && ret.vertices[i*dimension+j].position.y <= 3.3750)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(150 / 255.f, 156 / 255.f, 143 / 255.f); //pana aici ajunge
			}

			else
			{
				ret.vertices[i * dimension + j].color = glm::vec3(0, 0, 0);
			}
			
		}
}

void setPlaneMap(planeStr& ret)
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
		{
			ret.vertices[i * dimension + j].position.y = 0;
			ret.vertices[i * dimension + j].color = glm::vec3(20 / 255.f, 128 / 255.f, 20 / 255.f);
		}

}

void setColors(planeStr& ret)
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
		{
			if (ret.vertices[i * dimension + j].position.y < -8.0f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(70 / 255.f, 95 / 255.f, 115 / 255.f);
			}
			else if (ret.vertices[i * dimension + j].position.y >= -8.0f && ret.vertices[i*dimension + j].position.y <= -4.5f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(70 / 255.f, 95 / 255.f, 115 / 255.f);
			}
			else if (ret.vertices[i * dimension + j].position.y >= -4.5f && ret.vertices[i*dimension + j].position.y <= -3.9f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(73 / 255.f, 92 / 255.f, 39 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > -3.9f && ret.vertices[i*dimension + j].position.y <= -2.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(20 / 255.f, 128 / 255.f, 20 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > -2.f && ret.vertices[i*dimension + j].position.y <= 0.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(124 / 255.f, 145 / 255.f, 76 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > 0.f && ret.vertices[i*dimension + j].position.y <= 1.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(94.f / 255.f, 128 / 255.f, 51 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > 1.f && ret.vertices[i*dimension + j].position.y <= 7.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(75 / 255.f, 92 / 255.f, 64 / 255.f);
			}
			else if (ret.vertices[i*dimension + j].position.y > 7.f && ret.vertices[i*dimension + j].position.y <= 10.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(150 / 255.f, 156 / 255.f, 143 / 255.f); //pana aici ajunge
			}
			else if (ret.vertices[i*dimension + j].position.y > 10.f)
			{
				ret.vertices[i * dimension + j].color = glm::vec3(150 / 255.f, 156 / 255.f, 143 / 255.f);
			}
		}
	
}

void resetWorld()
{
	 nrOctaves = 6.0f; //1-6
	 frequency = 1.0;
	 amplitude = 0.5;
	 water = 1.f;
	 mountain = 1.f;
	 fallout = 0.665f;
}




class Game
{
private:

	//window
	GLFWwindow* window;
	const int width;
	const int height;
	int fbWidth;
	int fbHeight;

	//delta time
	float dt;
	float curTime;
	float lastTime;

	//mouse input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//camera
	Camera camera;

	//matrices
	glm::mat4 viewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 projectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;
	//shaders
	std::vector<Shader*> shaders;

	//textures
	std::vector<Texture*> textures;

	//Meshes
	std::vector<Mesh*> meshes;

	//Materials
	std::vector<Material*> materials;

	//lights
	std::vector<glm::vec3*> lights;

	//plane
	planeStr plane;

	//mouse picker
	MousePicker mp;

	//perlinNoise
	noise::utils::NoiseMap originalHM;
	noise::utils::NoiseMap waterHM;
	noise::utils::NoiseMap plainHM;
	noise::utils::NoiseMap hillHM;
	noise::utils::NoiseMap mountainHM;


	
	void initGLFW()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			std::cout << "ERROR::GLFW_INIT_FAILED\n";
			glfwTerminate();
		}
	}

	void initWin(const char* title)
	{
		/*Set the window options*/
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //opengl verion 4.4
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		this->window = glfwCreateWindow(this->width, this->height, title, NULL, NULL);
		
		if (this->window == nullptr)
		{
			std::cout << "ERROR::WINDOW_INTI_FAILED\n";
			glfwTerminate();
		}

		/*set canvas size*/
		glfwGetFramebufferSize(this->window, &this->fbWidth, &this->fbHeight);
		glViewport(0, 0, this->fbWidth, this->fbHeight);

		glfwMakeContextCurrent(this->window);
	}

	void initGLEW()
	{
		//INIT GLEW (needs window and opengl context)
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK)
		{
			std::cout << "ERROR::Game.h::GLEW_INIT_FAILED" << std::endl;
			glfwTerminate();
		}
	}

	void initOpenGL()
	{
		//OPENGL OPTIONS
		glEnable(GL_DEPTH_TEST); //for z coordonate

		//glEnable(GL_CULL_FACE); //to not draw what's behind
		/*glCullFace(GL_BACK);
		glFrontFace(GL_CCW);*/

		glEnable(GL_BLEND);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //GL_FILL / GL_LINE

		//input
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //puts cursor inside the window

	}

	void changePolygonModo(int mode)
	{
		if (mode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}

	void updateOpenGL(int mode)
	{
		if (mode) //1 pentru fill
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else //0 pentru line
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
	}

	void initMatrices()
	{
		/*this->viewMatrix = glm::mat4(1.f);
		this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);
		*/
		this->viewMatrix = glm::mat4(0.879389, -0.291357, 0.376544, 0.000000, 0.000000, 0.790887, 0.611962, 0.000000, -0.476103, -0.538153, 0.695498, 0.000000, -3.483938, 2.292052, -19.303074, 1.000000);
		this->projectionMatrix = glm::mat4(1.f);
		this->projectionMatrix = glm::perspective(glm::radians(this->fov),
			static_cast<float>(this->fbWidth) / this->fbHeight,
			this->nearPlane,
			this->farPlane
		);
	}

	void initShaders() 
	{
		
		char vertex[20] = "vertex_core.glsl";
		char fragment[20] = "fragment_core.glsl";
		char geometry[30] = "geometry_core.glsl";
		this->shaders.push_back(
			new Shader(vertex, fragment, geometry));
	/*	this->shaders.push_back(
			new Shader("vertex_core.glsl", "fragment_core.glsl", ""));*/
		//this->shaders.push_back(
		//	new Shader("vertex_sub.glsl", "fragment_sub.glsl", "geometry_sub.glsl"));
	}

	void initTextures() 
	{
		this->textures.push_back(
			new Texture("Images/water.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/sand.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/dirt1.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/grass2.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/hill1.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/mountain1.jpg", GL_TEXTURE_2D));
		this->textures.push_back(
			new Texture("Images/snow.jpg", GL_TEXTURE_2D));
	}

	void changeTextures(char* path)
	{
		switch (texMode)
		{
		case 1:
			this->textures[0]->loadFromFile(path); 
			break;
		case 2:
			this->textures[1]->loadFromFile(path);
			break;
		case 3:
			this->textures[2]->loadFromFile(path);
			break;
		case 4:
			this->textures[3]->loadFromFile(path);
			break;
		case 5:
			this->textures[4]->loadFromFile(path);
			break;
		case 6:
			this->textures[5]->loadFromFile(path);
			break;
		case 7:
			this->textures[6]->loadFromFile(path);
			break;
		default:
			break;
		}
	}

	void initMeshes()
	{
		//generate 4 quads using geometry shader -- not ok?
		this->meshes.push_back(
			new Mesh(&Quad(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))
		);

		makePlaneVertices(plane);
		makePlaneIndices(plane);
		setPlaneMap(plane);

		this->meshes.push_back(
			new Mesh(plane.vertices, plane.numVertices, plane.indices, plane.numIndices,
				glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))
		);
		this->meshes[MESH_PLANE]->printMesh();

	}

	void initMaterials() 
	{
		this->materials.push_back(
			new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 0, 1, 2, 3, 4, 5, 6));
	}

	void initLights()
	{
		this->lights.push_back(
			new glm::vec3(0.f, 0.f, 1.f)
		);
	}

	void initUniforms()
	{
		this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
		this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
		this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");

	
	}

	void updateUniforms()
	{
		//update view matrix (camera)
		this->viewMatrix = this->camera.getViewMatrix();
		this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->viewMatrix, "ViewMatrix");
		this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "camPosition");

		//update projection matrix
		this->projectionMatrix = glm::perspective(glm::radians(this->fov),
			static_cast<float>(this->fbWidth) / this->fbHeight,
			this->nearPlane,
			this->farPlane
		);

		this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->projectionMatrix, "ProjectionMatrix");
	}

	void initGui()
	{
		ImGuiContext* context = ImGui::CreateContext();
		ImGui::SetCurrentContext(context);
		ImGui_ImplGlfwGL3_Init(this->window, true);
		ImGui::StyleColorsDark();
	}

	bool select = false;
	void startSelection()
	{
		//selectionVec.clear();
		select = true;
	}
	void stopSelection()
	{
		select = false;

		auto end = selectionVec.end();
		for (auto it = selectionVec.begin(); it != end; ++it) {
			end = std::remove(it + 1, end, *it);
		}

		selectionVec.erase(end, selectionVec.end());

	/*	for (auto v : selectionVec)
		{
			std::cout << "Selected vertieces: " << v.x << " " << v.y << " " << v.z << "\n";
		}*/
	}

	void createWaterMap()
	{
		PerlinNoise *water = new PerlinNoise(dimension, mode);
		waterHM = water->getHeightMap();
	}
	void createPlainMap()
	{
		PerlinNoise *plain = new PerlinNoise(dimension, mode);
		plainHM = plain->getHeightMap();
	}
	void createHillMap()
	{
		PerlinNoise *hill = new PerlinNoise(dimension, mode);
		hillHM = hill->getHeightMap();
	}
	void createMountainMap()
	{
		PerlinNoise *mountain = new PerlinNoise(dimension, mode);
		mountainHM = mountain->getHeightMap();
	}

	void setViewMode(int mode)
	{
		if (mode)
		{
			this->shaders[SHADER_CORE_PROGRAM]->set1i(mode, "viewMode");
		}
		else
		{
			this->shaders[SHADER_CORE_PROGRAM]->set1i(mode, "viewMode");
		}
	}
	char* openFile() {
		OPENFILENAME ofn;
		char FilterSpec[70] = "All Files(.)\0*.*\0";
		char Title[8] = "Open...";
		char szFileName[MAX_PATH];
		char szFileTitle[MAX_PATH];

		*szFileName = 0; *szFileTitle = 0;

		/* fill in non-variant fields of OPENFILENAME struct. */
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetFocus();
		ofn.lpstrFilter = FilterSpec;
		ofn.lpstrCustomFilter = NULL;
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = szFileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrInitialDir = "."; // Initial directory.
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle = Title;
		ofn.lpstrDefExt = 0;//I've set to null for demonstration

		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

		if (!GetOpenFileName((LPOPENFILENAME)&ofn))
		{
			return NULL; // Failed or cancelled
		}
		else
		{
			return szFileName;
		}
	}
	char* openTextFile() {
		OPENFILENAME ofn;
		char FilterSpec[70] = "All Files(.)\0*.*\0";
		char Title[8] = "Open...";
		char szFileName[MAX_PATH];
		char szFileTitle[MAX_PATH];

		*szFileName = 0; *szFileTitle = 0;

		/* fill in non-variant fields of OPENFILENAME struct. */
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetFocus();
		ofn.lpstrFilter = FilterSpec;
		ofn.lpstrCustomFilter = NULL;
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = szFileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrInitialDir = "."; // Initial directory.
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrTitle = Title;
		ofn.lpstrDefExt = 0;//I've set to null for demonstration

		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

		if (!GetOpenFileName((LPOPENFILENAME)&ofn))
		{
			return NULL; // Failed or cancelled
		}
		else
		{
			return szFileName;
		}
	}

	char* getLastWords(char* string)
	{
		std::string str(string);
		std::string word = "";
	
		int len = str.length();
		std::string last_word;
		int i = len - 1;

		while (i >= 0 && str[i] != '\\')
		{
			i--;
		}

		for (int j = i + 1; j < len; j++)
		{
			last_word += str[j];
		}
		

		int newLen = last_word.length();
		const int size = newLen + 1;
		char *char_arr = new char[size];
		strcpy(char_arr, last_word.c_str());

		for (int i = 0; i < newLen; i++)
			cout << char_arr[i];
		std::cout << "\n";
		return char_arr;
	}

	void writeToFile()
	{
		std::fstream file;
		file.open("Terrain.txt", ios::out);
		if (!file)
		{
			std::cout << "File not created\n";
		}
		else
		{
			cout << "File created successfully\n";
			file << dimension;
			file << "#";
			file << "\n";


			for (int i = 0; i < dimension; i++)
				for (int j = 0; j < dimension; j++)
				{
					std::cout << plane.vertices[i * dimension + j].position.y << std::endl;
					file << plane.vertices[i * dimension + j].position.y;
					file << "#";
					file << "\n";
				}
			file.close();
		}
	}
	std::pair<int, std::vector<double>> readFile(char* path)
	{
		std::fstream file;
		file.open(path, ios::in);
		std::vector<char> terrain;
		if (!file)
		{
			std::cout << "No such file!\n";
		}
		else
		{
			char ch;
			terrain.clear();
			while (1)
			{
				file >> ch;
				//std::cout << ch << " ";
				terrain.push_back(ch);
				
				if (file.eof())
				{
					break;
				}
			
			}
		}


		int nd = (terrain[0] - '0') * 10 + (terrain[1] - '0');
		std::cout << nd << std::endl;

		std::vector<double> heights;
		int pos;
		double y;
		std::string ss;
		for (int i = 2; i < terrain.size() - 1; i++)
		{
			if ((terrain[i] == '#') && !(i == terrain.size() - 2))
			{
				ss = "";
				pos = i + 1;
				for (int j = pos; j < terrain.size(); j++)
				{
					if (terrain[j] != '#')
					{
						ss += terrain[j];
					}
					else
					{
						heights.push_back(std::stod(ss));
						break;
					}

				}
				
			}
		}

		//for (auto a : heights)
		//{
		//	std::cout << a << std::endl;
		//}



		std::pair <int, std::vector<double>> pair = std::make_pair(nd, heights);

		return pair;
	}

	void updateMeshImport(std::pair <int, std::vector<double>> pair, planeStr& plane)
	{
		for (int i = 0; i < dimension; i++)
		{
			plane.vertices[i].position.y = pair.second[i];
		}
	}
	//-------------------------------------------------------------------------------
	//-----------------------------MENU----------------------------------------------
	bool colors = false;
	void renderGui()
	{
		ImGui_ImplGlfwGL3_NewFrame();
		//-------------------------
	
		if (perlin)
		{
			ImGui::Text("PerlinNoise options");
			ImGui::SliderFloat("Octaves", &nrOctaves, 1.0f, 8.0f);
			ImGui::SliderFloat("Frequency", &frequency, 1.0f, 6.0f);
			ImGui::SliderFloat("Amplitude", &amplitude, 0.1f, 1.f);
			ImGui::SliderFloat("Fallout", &fallout, 0.0f, 1.f);
			/*ImGui::SliderFloat("Water", &water, -5.f, 5.f);
			ImGui::SliderFloat("Mountain", &mountain, -5.f, 5.f);*/
			ImGui::Text("Reset all modification to initial terrain");
			if (ImGui::Button("Reset"))
			{
				resetWorld();
			}
		}
		
		if (distroy)
		{
			if (ImGui::Button("Stop Generation"))
			{
				generation = false;
				perlin = false;
				startSelection();
				distroy = false;
			}
		}
		

		if(!generation)
		{
			ImGui::Spacing();
			ImGui::Text("Modify elevation of chosen vertices:");
			ImGui::SliderFloat("Size", &elevationSize, -1.0f, 1.0f);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Change brush size:");
			ImGui::SliderInt("", &veciniSize, 1, 10);
			ImGui::Spacing();
			ImGui::Text("Choose a preset brush for:");
			if (ImGui::Button("Water"))
			{
				mode = 1;
				startModeDrawing = true;
				createWaterMap();
			}
			ImGui::SameLine();
			if (ImGui::Button("Plain"))
			{
				startModeDrawing = true;
				mode = 2;
				createPlainMap();
			}
			ImGui::SameLine();
			if (ImGui::Button("Hill"))
			{
				startModeDrawing = true;
				mode = 3;
				createHillMap();
			}
			ImGui::SameLine();
			if (ImGui::Button("Mountain"))
			{
				startModeDrawing = true;
				mode = 4;
				createMountainMap();
			}
			ImGui::Text("Resets terrain to plain:");
			if (ImGui::Button("Leveling"))
			{
				startModeDrawing = true;
				mode = -1;
			}
			ImGui::Text("Resets terrain modification mode de default");
			if (ImGui::Button("Reset Mode"))
			{
				mode = 0;
				startModeDrawing = false;
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Choose the way of viewing the terrrain");
			if (ImGui::Button("Wire View"))
			{
				viewMode = 0;
				setViewMode(viewMode);
				changePolygonModo(viewMode);
			}
			ImGui::SameLine();
			if (ImGui::Button("Texture View"))
			{
				viewMode = 1;
				setViewMode(viewMode);
				changePolygonModo(viewMode);
			}
			ImGui::Spacing();
			/*if (ImGui::Button("Export Model"))
			{
				exportModel();
			}*/
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Choose Terrain type to pe textured:");
			if (ImGui::Button("Water_"))
			{
				texMode = 1;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Sand_"))
			{
				texMode = 2;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Dirt_"))
			{
				texMode = 3;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Grass_"))
			{
				texMode = 4;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Hill_"))
			{
				texMode = 5;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Mountain_"))
			{
				texMode = 6;
				std::cout << texMode << std::endl;
			}
			if (ImGui::Button("Snow_"))
			{
				texMode = 7;
				std::cout << texMode << std::endl;
			}
			ImGui::Text("Import Texture:");
			if (ImGui::Button("Choose Texture"))
			{
				changeTextures(getLastWords(openFile()));
			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Export Terrain");
			if (ImGui::Button("Export"))
			{
				writeToFile();
			}
			ImGui::Text("Import Terrain");
			if (ImGui::Button("Import"))
			{

				pairFunc = readFile(getLastWords(openTextFile()));
				dimension = pairFunc.first;

				stopDimension = true;
				importVar = true;

			}
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Button("Reset entire program from beginning"))
			{
				resetAllApp();
			}
		}


		//-------------------------	

		if (showWindow)
		{
			if (!ImGui::Begin("Input Manager", &showWindow))
			{
				ImGui::End();
			}
			else
			{
				ImGui::Text("Terrain dimension:");
				ImGui::SliderInt("Dim x Dim", &dimension, 10, 70);

				ImGui::Text("Generate terrain with PerlinNoise?");
				if (ImGui::Button("PerlinNoise Terrain"))
				{
					setHeightMap(plane);
					perlin = true;
					showWindow = false;
					stopDimension = true;
				}
				ImGui::SameLine();
				if (ImGui::Button("Plane Terrain"))
				{
					setPlaneMap(plane);
					perlin = false;
					generation = false;
					showWindow = false;
					stopDimension = true;
					distroy = false;
				}
				ImGui::End();
			}
		}


		if (!ImGui::Begin("FPS Counter", &showWindow))
		{
			ImGui::End();
		}
		else
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
			ImGui::End();
		}

		
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	}
	//-------------------------------------------------------------------------------
	std::pair<int,int> findCoords(planeStr& ret, glm::vec3 svec)
	{
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++)
			{
				if (ret.vertices[i * dimension + j].position.x == svec.x && ret.vertices[i * dimension + j].position.y == svec.y && ret.vertices[i * dimension + j].position.z == svec.z)
				{
					return std::make_pair(i, j);
				}
			}
		return std::make_pair(NULL, NULL);
	}
	void changeElevation(planeStr& ret, float size)
	{
		
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{ 
			auto end = selectionVec.end();
			for (auto it = selectionVec.begin(); it != end; ++it) {
				end = std::remove(it + 1, end, *it);
			}

			selectionVec.erase(end, selectionVec.end());

			std::vector<glm::vec3> neighbours;
			for (auto svec : selectionVec)
			{
				for (int i = 0; i < dimension; i++)
					for (int j = 0; j < dimension; j++)
					{
						if (ret.vertices[i * dimension + j].position.x == svec.x && ret.vertices[i * dimension + j].position.y == svec.y && ret.vertices[i * dimension + j].position.z == svec.z)
						{
							//neighbours = this->meshes[MESH_PLANE]->findNeighbours(ret.vertices[i * dimension + j].position);
							neighbours = this->meshes[MESH_PLANE]->tryThis((ret.vertices[i * dimension + j].position), veciniSize);
							ret.vertices[i * dimension + j].position.y += size;
							for (auto a : neighbours)
							{
								//std::cout << a.x << " " << a.y << " " << a.z << "\n";
								std::pair<int, int> ij = findCoords(ret, a);
								//std::cout << ij.first << " " << ij.second << std::endl;
								if(ij.first != 0 && ij.second != 0)
								ret.vertices[ij.first * dimension + ij.second].position.y += size / 3;
							}
						}
					}
			}
		}
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
		{
			selectionVec.clear();
		}

	}

	void applyModeMesh(planeStr& ret, float size, int mode)
	{
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			auto end = selectionVec.end();
			for (auto it = selectionVec.begin(); it != end; ++it) {
				end = std::remove(it + 1, end, *it);
			}

			selectionVec.erase(end, selectionVec.end());


			std::vector<glm::vec3> neighbours;
			for (auto svec : selectionVec)
			{
				for (int i = 0; i < dimension; i++)
					for (int j = 0; j < dimension; j++)
					{
						if (ret.vertices[i * dimension + j].position.x == svec.x && ret.vertices[i * dimension + j].position.y == svec.y && ret.vertices[i * dimension + j].position.z == svec.z)
						{
						
							neighbours = this->meshes[MESH_PLANE]->tryThis((ret.vertices[i * dimension + j].position), veciniSize);
							switch (mode)
							{
							case 1:
								if (ret.vertices[i * dimension + j].position.y > waterHM.GetValue(i, j))
								{
									ret.vertices[i * dimension + j].position.y -= 0.5;
								}
								//ret.vertices[i * dimension + j].position.y = waterHM.GetValue(i, j);
								for (auto a : neighbours)
								{
									std::pair<int, int> ij = findCoords(ret, a);
									if (ij.first != 0 && ij.second != 0)
									{
										if (ret.vertices[ij.first * dimension + ij.second].position.y > waterHM.GetValue(ij.first, ij.second))
											ret.vertices[ij.first * dimension + ij.second].position.y -= 0.2;
										//ret.vertices[ij.first * dimension + ij.second].position.y = waterHM.GetValue(ij.first, ij.second);
									}
								}
								break;
							case 2:

								ret.vertices[i * dimension + j].position.y = plainHM.GetValue(i,j);
								for (auto a : neighbours)
								{
									std::pair<int, int> ij = findCoords(ret, a);
									if (ij.first != 0 && ij.second != 0)
									{
										if (ret.vertices[ij.first * dimension + ij.second].position.y > plainHM.GetValue(ij.first, ij.second))
										ret.vertices[ij.first * dimension + ij.second].position.y -= 0.1;
										if (ret.vertices[ij.first * dimension + ij.second].position.y < plainHM.GetValue(ij.first, ij.second))
											ret.vertices[ij.first * dimension + ij.second].position.y += 0.1;

									}
								}
								break;
							case 3:
								ret.vertices[i * dimension + j].position.y = hillHM.GetValue(i, j);
								for (auto a : neighbours)
								{
									std::pair<int, int> ij = findCoords(ret, a);
									if (ij.first != 0 && ij.second != 0)
									{
										if (ret.vertices[ij.first * dimension + ij.second].position.y > hillHM.GetValue(ij.first, ij.second))
											ret.vertices[ij.first * dimension + ij.second].position.y -= 0.3;
										if (ret.vertices[ij.first * dimension + ij.second].position.y < hillHM.GetValue(ij.first, ij.second))
											ret.vertices[ij.first * dimension + ij.second].position.y += 0.3;

									}
								}
								break;
							case 4:
								ret.vertices[i * dimension + j].position.y = mountainHM.GetValue(i, j);
								for (auto a : neighbours)
								{
									std::pair<int, int> ij = findCoords(ret, a);
									if (ij.first != 0 && ij.second != 0)
									{
										if (ret.vertices[ij.first * dimension + ij.second].position.y < mountainHM.GetValue(ij.first, ij.second))
											ret.vertices[ij.first * dimension + ij.second].position.y += 0.2;
									}
								}
								break;
							case -1:
								ret.vertices[i * dimension + j].position.y = 0.0f;
								for (auto a : neighbours)
								{
									std::pair<int, int> ij = findCoords(ret, a);
									if (ij.first != 0 && ij.second != 0)
									{
										ret.vertices[ij.first * dimension + ij.second].position.y = 0.f;
									}
								}
								break;
							default:
								break;
							}
							
						}

					}
			}

		}
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
		{
			selectionVec.clear();
		}
	}

	void updateMesh()
	{
		if (!stopDimension)
		{
			makePlaneVertices(plane);
			makePlaneIndices(plane);
		}
	
		if (generation)
		{
			if (perlin)
			{
				setHeightMap(plane);
			}
			else
			{
				setPlaneMap(plane);
			}
		}
		else
		{
		
			if (!startModeDrawing)
			{
				changeElevation(plane, elevationSize);
			}
			else
			{
				applyModeMesh(plane, elevationSize, mode);
			}
			if (importVar)
			{

				for (int i = 0; i < dimension; i++)
					for (int j = 0; j < dimension; j++)
					{
						plane.vertices[i * dimension + j].position.y = pairFunc.second[i * dimension + j];
					}
				//for (int i = 0; i < dimension; i++)
				//{
				//	std::cout << "aaaa" << plane.vertices[i].position.y << std::endl;
				//}
				importVar = false;
			}
			
		}

		setColors(plane);

		meshes[MESH_PLANE]->update(plane.vertices, plane.numVertices, plane.indices, plane.numIndices);
	
	}

	//-------------------------------------------------------------------------------
	//--------------------------CHECK HIT--------------------------------------------
	glm::vec3 ClosestPoint(glm::vec3 A, glm::vec3 B, glm::vec3 P) //Q va fi cel mai aropiat punct de pe linia AB la P
	{
		glm::vec3 AB = B - A;
		float ab2 = glm::dot(AB, AB);
		glm::vec3 AP = P - A;
		float ap_dot_ab = glm::dot(AP, AB);
		float t = ap_dot_ab / ab2; // the projection parameter on the line   
		 // clamp parameter to segment extremities    
		if (t < 0.0f) t = 0.0f;
		else if (t > 1.0f) t = 1.0f;
		// calculate the closest point   
		glm::vec3 Q = A + AB * t;
		return Q;
	}

	bool PointInSphere(glm::vec3 P, float r, glm::vec3 Q)
	{
		glm::vec3 PQ = Q - P;
		float pq2 = glm::dot(PQ, PQ);
		float r2 = r * r;
		if (pq2 > r2) return false;
		else return true;
	}
	//--------------------------------------------------------
	glm::mat4 getModelViewMatrix()
	{
		return this->viewMatrix * this->meshes[MESH_PLANE]->getModelMatrix();
	}

	glm::vec3 ExtractCameraPos(const glm::mat4 & a_modelView)
	{

		glm::mat4 modelViewT = transpose(a_modelView);

		// Get plane normals 
		glm::vec3 n1(modelViewT[0]);
		glm::vec3 n2(modelViewT[1]);
		glm::vec3 n3(modelViewT[2]);

		// Get plane distances
		float d1(modelViewT[0].w);
		float d2(modelViewT[1].w);
		float d3(modelViewT[2].w);

		// Get the intersection of these 3 planes
		glm::vec3 n2n3 = cross(n2, n3);
		glm::vec3 n3n1 = cross(n3, n1);
		glm::vec3 n1n2 = cross(n1, n2);

		glm::vec3 top = (n2n3 * d1) + (n3n1 * d2) + (n1n2 * d3);
		float denom = dot(n1, n2n3);

		return top / -denom;
	}

	double distanceVec (glm::vec3 A, glm::vec3 B)
	{
		return std::sqrt(std::pow((B.x - A.x), 2) + std::pow((B.y - A.y), 2) + std::pow((B.z - A.z), 2));
	}

	
	void checkHit(glm::vec3 camPos, glm::vec3 dir, planeStr plane)
	{
		float distance = 1000;
		bool pointInSpeher = false;
		glm::vec3 end(dir.x * distance, dir.y * distance, dir.z * distance);

		glm::vec3 vertexPoint;
		std::vector<glm::vec3> vec;
		vec.clear();
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++)
			{
				vertexPoint = plane.vertices[i * dimension + j].position;
				glm::vec3 closestePoint = ClosestPoint(camPos, end, vertexPoint);
				
				float rad = 0.5;
				if (PointInSphere(vertexPoint, rad, closestePoint))
				{
					pointInSpeher = true;
					//std::cout << glm::to_string(closestePoint) << "  " << glm::to_string(vertexPoint) << std::endl << std::endl;
					vec.push_back(vertexPoint);
				}
			}
		if (pointInSpeher)
		{
			glm::vec3 camera = ExtractCameraPos(getModelViewMatrix());
			double min = 10000;
			double aux;
			int pos;
			for (int i = 0; i < vec.size(); i++)
			{
				//std::cout << vec[i].x << " " << vec[i].y << " " <<vec[i].z << "\n --";
				aux = distanceVec(camera, vec[i]);
				if (aux < min)
				{
					min = aux;
					pos = i;
				}
			}
			hitVertex = vec[pos];
			//std::cout << vec[pos].x << " " << vec[pos].y << " " << vec[pos].z << "--\n ";
			if (select)
			{
				selectionVec.push_back(hitVertex);
			}
			
		}
		//std::cout << "------" << std::endl;
		
	}
	//-------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------

	void resetAllApp()
	{

		this->camera = Camera(glm::vec3(11.f, 10.f, 13.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		this->mp = MousePicker(this->viewMatrix, this->width, this->height);

		 stopDimension = false;
		 perlin = false;
		 generation = true;

		 veciniSize = 1;
		 startModeDrawing = false;
		 viewMode = 0;
		 wireMode = 0;

		 showWindow = true;
		 dimension = 40;
		 distroy = true;


		 this->textures[0] = new Texture("water.jpg", GL_TEXTURE_2D);
		 this->textures[1] = new Texture("sand.jpg", GL_TEXTURE_2D);
		 this->textures[2] = new Texture("dirt1.jpg", GL_TEXTURE_2D);
		 this->textures[3] = new Texture("grass2.jpg", GL_TEXTURE_2D);
		 this->textures[4] = new Texture("hill1.jpg", GL_TEXTURE_2D);
		 this->textures[5] = new Texture("mountain1.jpg", GL_TEXTURE_2D);
		 this->textures[6] = new Texture("snow.jpg", GL_TEXTURE_2D);
	}

public:
	Game(const char* title, const int width, const int height) : 
		width(width), 
		height(height), 
		camera(glm::vec3(11.f,10.f,13.f),     //(glm::vec3(0.f,1.f,0.f)
			glm::vec3(0.f, 1.f, 0.f), 
			glm::vec3(0.f,1.f,0.f)),
		mp(this->viewMatrix, this->width, this->height)
	{
		this->window = nullptr;
		this->fbHeight = this->height;
		this->fbWidth = this->width;
	
		this->camPosition = glm::vec3(0.f, 0.f, 1.f);
		this->worldUp = glm::vec3(0.f, 1.f, 0.f);
		this->camFront = glm::vec3(0.f, 0.f, -1.f);

		this->fov = 90.f;
		this->nearPlane = 0.1f;
		this->farPlane = 1000.f;

		this->dt = 0.0f;
		this->curTime = 0.f;
		this->lastTime = 0.f;

		this->lastMouseX = 0.0;
		this->lastMouseY = 0.0;
		this->mouseX = 0.0;
		this->mouseY = 0.0;
		this->mouseOffsetX = 0.0;
		this->mouseOffsetY = 0.0;
		this->firstMouse = true;

		this->initGLFW();
		this->initWin(title);
		this->initGLEW();
		this->initOpenGL();
		this->initMatrices();
		this->initShaders();
		this->initTextures();
		this->initMaterials();
		this->initMeshes();
		this->initLights();
		this->initUniforms();
		this->initGui();
	}
	virtual ~Game()
	{
		//clear GUI
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();

		//clear Window
		glfwDestroyWindow(this->window);
		glfwTerminate();

		for (size_t i = 0; i < this->shaders.size(); i++)
		{
			delete this->shaders[i];
		}
		for (size_t i = 0; i < this->textures.size(); i++)
		{
			delete this->textures[i];
		}
		for (size_t i = 0; i < this->meshes.size(); i++)
		{
			delete this->meshes[i];
		}
		for (size_t i = 0; i < this->materials.size(); i++)
		{
			delete this->materials[i];
		}
		for (size_t i = 0; i < this->lights.size(); i++)
		{
			delete this->lights[i];
		}
	}

//accessors
	GLFWwindow* getWindow()
	{
		return this->window;
	}


//modifiers
	void windowClose()
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

//functions
	void updateKeyboardInput()
	{
		if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			windowClose();
		}

		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			this->dt = this->dt * 3;
		}

		if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
		{
			this->camera.move(this->dt, FORWARD);
		}
		if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
		{
			this->camera.move(this->dt, BACK);
		}
		if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
		{
			this->camera.move(this->dt, LEFT);
		}
		if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
		{
			this->camera.move(this->dt, RIGHT);
		}
		if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			this->camera.move(this->dt, UP);
		}
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			this->camera.move(this->dt, DOWN);
		}
	}

	void updateMouseInput()
	{
		glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY); //save current mouse pos

		if (this->firstMouse) //initial settings
		{
			this->lastMouseX = this->mouseX;
			this->lastMouseY = this->mouseY;
			firstMouse = false;
		}

		//offset
		this->mouseOffsetX = this->mouseX - this->lastMouseX;
		this->mouseOffsetY = this->lastMouseY - this->mouseY;

		//set last x and y
		this->lastMouseX = mouseX;
		this->lastMouseY = mouseY;
	}

	void updateDt()
	{
		this->curTime = static_cast<float>(glfwGetTime());
		this->dt = this->curTime - this->lastTime;
		this->lastTime = this->curTime;

	}

	void updateInput()
	{
		glfwPollEvents();
		this->updateKeyboardInput();
		this->updateMouseInput();
		bool isPressed = false;
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
		{
			isPressed = true;
		}
		this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY, isPressed);
	}


	void seeIfHit()
	{
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		{
			glm::vec3 camera = ExtractCameraPos(getModelViewMatrix());
			checkHit(camera, mp.getCurrentRay(), this->plane);
		}
	}

	
	void update()
	{
		this->updateDt();
		this->updateInput();
		/*std::cout << "Delta Time: " << this->dt << "\n"
			<< "Mouse offsetX :" << this->mouseOffsetX << "\n"
			<< "Mouse offsetY :" << this->mouseOffsetY << "\n";*/

	}

	void render()
	{
		
		//DRAW
			//clear
		glClearColor(0.f, 0.f, 0.f, 1.f); // R G B A(transparancy) -- clear the specific color form screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		//-----------------------------------------UPDATE UNIFORMS--------------------------------
		//update uniforms - how to send to vertex
		this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
		updateUniforms();

		//update projection matrix
		projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(fbWidth) / fbHeight, nearPlane, farPlane);
		this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(projectionMatrix, "ProjectionMatrix");
		//-----------------------------------------------------------------------------------------

	
		//use a program
		this->shaders[SHADER_CORE_PROGRAM]->use();

		//activate texture
		this->textures[WATER]->bind(0);
		this->textures[SAND]->bind(1);
		this->textures[DIRT]->bind(2);
		this->textures[GRASS]->bind(3);
		this->textures[HILL]->bind(4);
		this->textures[MOUNTAIN]->bind(5);
		this->textures[SNOW]->bind(6);

		//draw
		this->meshes[MESH_PLANE]->render(this->shaders[SHADER_CORE_PROGRAM]);
		
		//render UI
		colors = false;
		this->renderGui();
		this->updateMesh();
		
		
		//coordonatele mouse-ului
		mp.update(this->viewMatrix, this->projectionMatrix, this->mouseX, this->mouseY);

		//check for collisions
		seeIfHit();
		
		//std::cout << glm::to_string(viewMatrix) << std::endl << std::endl;
		//end draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

};
#endif
