#pragma once
#include "../stdafx.h"
#include "SmoothGroup.h"
#include "Group.h"
#include "FixedArray.h"

using namespace std;
class ObjModel
{
private:
	string m_filename;
	string m_name;
	float m_scale;
	float m_x;
	float m_y;
	float m_z;
	float m_rx;
	float m_ry;
	float m_rz;
	float m_colors[32][3];

public:
	
	typedef FixedArray<Group*> GroupList;
	GroupList* m_textureGroups;

	ObjModel(void);
	ObjModel(string filename,string name, FixedArray<Group> groups, vector<SmoothGroup> smoothgroups);
	ObjModel(string filename);
	~ObjModel(void);

	void draw();
	string toString();
	ObjModel& getTestModel();
	void setGroups(GroupList* m_groupList);
	void rotate(float x,float y,float z);
	void translate(float x, float y,float z);
	void scale(float scaleSize);
};

