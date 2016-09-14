#include "../inc/Group.h"
#include <sstream>

Group::Group(){
	m_name = "Default";
	m_material = NULL;
}

Group::~Group(){
	/*cout << "Delete group: ";
	cout << m_name << endl;*/
}

Group::Group(string name){
	m_name = name;
	m_material = NULL;
}

Group::Group(string name, Group::TriangleList* triangles){
	m_name = name;
	m_triangles = triangles;
	m_material = NULL;
}

string Group::toString(void){
	ostringstream output;
	output << "Group: " << m_name << endl
	       << "Material: ";
	if(m_material == NULL)
		output << "No Material" <<endl;
	else
		output << m_material->m_name <<endl;
	output << "Triangles: " << m_triangles->size();
	return output.str();
}

Group::TriangleList* Group::getTriangleList(){
	return m_triangles;
}

void Group::setTriangleList(TriangleList* triangleList){
	m_triangles = triangleList;
}

void Group::setMaterial(Material* m){
	m_material = m;
}

string Group::getName(){
	return m_name;
}

Material* Group::getMaterial()
{
	return m_material;
}
