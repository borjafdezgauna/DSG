#pragma once
class ColladaModel
{
	char* modelo;
public:
	ColladaModel(char* fileName);
	~ColladaModel();
	void draw();
};

