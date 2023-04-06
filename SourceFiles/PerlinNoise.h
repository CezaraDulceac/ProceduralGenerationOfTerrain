#pragma once
#include<iostream>
#include<noise/noise.h>
#include"noiseutils.h"


class PerlinNoise
{
private:
	int dimension;
	float nrOctaves;
	float frequency;
	float amplitude;
	float falloff;

	glm::vec2 ld;
	glm::vec2 ru;

	noise::module::Perlin terrainType; //use only this for simple perlin
	noise::module::RidgedMulti mountainTerrain;
	noise::module::Billow baseFlatTerrain;
	noise::module::ScaleBias flatTerrain;
	noise::module::Select finalTerrain; //use this for complex results

	noise::utils::NoiseMap heightMap;
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;


	void initModule()
	{
		terrainType.SetOctaveCount(nrOctaves); //6 is default octaves for perlin noise
		terrainType.SetFrequency(frequency); //increase/decrease features - frequency
		terrainType.SetPersistence(amplitude); //increase/decrease amplitudes - cat de "smooth" sa fie
	}

	void initTerrainType()
	{
		baseFlatTerrain.SetFrequency(2.0); //for smaller more numerous lumps in the flat terrain

		flatTerrain.SetSourceModule(0, baseFlatTerrain);
		flatTerrain.SetScale(0.125); //flatten the lumps (1/8)
		flatTerrain.SetBias(-0.2); //reduces the elevations of the lumps to aprox -1

		finalTerrain.SetSourceModule(0, flatTerrain);
		finalTerrain.SetSourceModule(1, mountainTerrain);
		finalTerrain.SetControlModule(terrainType);
		finalTerrain.SetBounds(0.0, 1000.0);
		finalTerrain.SetEdgeFalloff(falloff);
	}

	void initMapBuilder()
	{
		heightMapBuilder.SetSourceModule(finalTerrain); //ia de aici
		heightMapBuilder.SetDestNoiseMap(heightMap); //si baga aici

		heightMapBuilder.SetDestSize(dimension, dimension); //size of the noise map
		heightMapBuilder.SetBounds(ld.x, ru.x, ld.y, ru.y); //(2,1) si (6,5) --bottom left and upper right
		heightMapBuilder.Build();
	}

public:
	PerlinNoise(int dimension, float nrOctaves, float frequency, float amplitude, float fallout,
		glm::vec2 ld, glm::vec2 ru)
	{
		this->dimension = dimension;
		this->nrOctaves = nrOctaves;
		this->frequency = frequency;
		this->amplitude = amplitude;
		this->falloff = fallout;
		this->ld = ld;
		this->ru = ru;

		initModule();
		initTerrainType();
		initMapBuilder();
	}

	PerlinNoise(int dimension, int mode)
	{
		switch (mode)
		{
		case 1: //water mode
			this->dimension = dimension;
			this->nrOctaves = 1.484;
			this->frequency = 5.207;
			this->amplitude = 0.276;
			this->falloff = 1.0;
			this->ld.x = 4;
			this->ld.y = 4;
			this->ru.x = 20;
			this->ru.y = 20;

			initModule();
			initTerrainType();
			initMapBuilder();

			for (int i = 0; i < dimension; i++)
				for (int j = 0; j < dimension; j++)
				{
					float aux = heightMap.GetValue(i, j);
					heightMap.SetValue(i, j, aux - 6);
				}
			break;
		case 2: //plain mode
			this->dimension = dimension;
			this->nrOctaves = 8.0;
			this->frequency = 1.0;
			this->amplitude = 0.5;
			this->falloff = 1.0;
			this->ld.x = 4;
			this->ld.y = 4;
			this->ru.x = 10;
			this->ru.y = 10;

			initModule();
			initTerrainType();
			initMapBuilder();

			for (int i = 0; i < dimension; i++)
				for (int j = 0; j < dimension; j++)
				{
					float aux = heightMap.GetValue(i, j);
					heightMap.SetValue(i, j, aux - 1.2);
				}

			break;
		case 3: //hill
			this->dimension = dimension;
			this->nrOctaves = 1.0;
			this->frequency = 1.0;
			this->amplitude = 0.36;
			this->falloff = 1.0;
			this->ld.x = 2.f;
			this->ld.y = 1.f;
			this->ru.x = 6.f;
			this->ru.y = 5.f;

			initModule();
			initTerrainType();
			initMapBuilder();

			for (int i = 0; i < dimension; i++)
				for (int j = 0; j < dimension; j++)
				{
					float aux = heightMap.GetValue(i, j);
					heightMap.SetValue(i, j, aux + 0.7);
				}
			break;
		case 4: //mountain
			this->dimension = dimension;
			this->nrOctaves = 1.0;
			this->frequency = 1.0;
			this->amplitude = 0.36;
			this->falloff = 1.0;
			this->ld.x = 2;
			this->ld.y = 1;
			this->ru.x = 6;
			this->ru.y = 5;

			initModule();
			initTerrainType();
			initMapBuilder();

			for (int i = 0; i < dimension; i++)
				for (int j = 0; j < dimension; j++)
				{
					float aux = heightMap.GetValue(i, j);
					heightMap.SetValue(i, j, aux + 3);
				}
			break;
		}
		
		

	}
	~PerlinNoise(){}

//accessors
	noise::utils::NoiseMap getHeightMap()
	{
		return this->heightMap;
	}

	int getDimension()
	{
		return this->dimension;
	}

	void updatePerlinNoise(int dimension, float nrOctaves, float frequency, float amplitude, float fallout,
		glm::vec2 ld, glm::vec2 ru)
	{
		this->dimension = dimension;
		this->nrOctaves = nrOctaves;
		this->frequency = frequency;
		this->amplitude = amplitude;
		this->falloff = falloff;
		this->ld = ld;
		this->ru = ru;
	}


	noise::utils::NoiseMap getWaterTerrain()
	{
		noise::module::Perlin terrainType; //use only this for simple perlin
		//noise::module::RidgedMulti mountainTerrain;
		noise::module::Billow baseFlatTerrain;
		noise::module::ScaleBias flatTerrain;
		noise::module::Select finalTerrain; //use this for complex results

		noise::utils::NoiseMap heightMap1;
		noise::utils::NoiseMapBuilderPlane heightMapBuilder;


		terrainType.SetOctaveCount(1.484); //6 is default octaves for perlin noise
		terrainType.SetFrequency(5.207); //increase/decrease features - frequency
		terrainType.SetPersistence(0.275); //increase/decrease amplitudes - cat de "smooth" sa fie

		baseFlatTerrain.SetFrequency(2.0); //for smaller more numerous lumps in the flat terrain

		flatTerrain.SetSourceModule(0, baseFlatTerrain);
		flatTerrain.SetScale(0.125); //flatten the lumps (1/8)
		flatTerrain.SetBias(-0.2); //reduces the elevations of the lumps to aprox -1

		finalTerrain.SetSourceModule(0, flatTerrain);
		//finalTerrain.SetSourceModule(1, mountainTerrain);
		finalTerrain.SetControlModule(terrainType);
		finalTerrain.SetBounds(0.0, 1000.0);
		finalTerrain.SetEdgeFalloff(1.0);

		heightMapBuilder.SetSourceModule(finalTerrain); //ia de aici
		heightMapBuilder.SetDestNoiseMap(heightMap); //si baga aici

		heightMapBuilder.SetDestSize(dimension, dimension); //size of the noise map
		heightMapBuilder.SetBounds(2, 6, 1, 5); //(2,1) si (6,5) --bottom left and upper right
		heightMapBuilder.Build();

		/*for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++)
			{
				float aux = heightMap1.GetValue(i, j);
				if (aux > 0)
				{
					heightMap1.SetValue(i, j, aux * -5);
				}
				else
				{
					heightMap1.SetValue(i, j, aux * 5);
				}
			}*/

		return heightMap;
	}

	void exportHeightMap(noise::utils::NoiseMap heightmap)
	{
		utils::RendererImage renderer;
		utils::Image image;
		renderer.SetSourceNoiseMap(heightmap);
		renderer.SetDestImage(image);
		renderer.ClearGradient();
		renderer.AddGradientPoint(-1.00, utils::Color(32, 160, 0, 255)); // grass
		renderer.AddGradientPoint(-0.25, utils::Color(224, 224, 0, 255)); // dirt
		renderer.AddGradientPoint(0.25, utils::Color(128, 128, 128, 255)); // rock
		renderer.AddGradientPoint(1.00, utils::Color(255, 255, 255, 255)); // snow
		renderer.EnableLight();
		renderer.SetLightContrast(3.0);
		renderer.SetLightBrightness(2.0);
		renderer.Render();

		utils::WriterBMP writer;
		writer.SetSourceImage(image);
		writer.SetDestFilename("heightmap.bmp");
		writer.WriteDestFile();
	}

	

};