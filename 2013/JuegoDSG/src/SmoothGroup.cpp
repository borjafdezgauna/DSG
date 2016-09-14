#include "../inc/SmoothGroup.h"
#include "../inc/Vertex.h"
#include <sstream>
#include <map> 

using namespace std;


SmoothGroup::SmoothGroup(int smoothId){
	m_triangles = NULL;
	m_has_vn = true;
	m_smoothId = smoothId;
}

SmoothGroup::~SmoothGroup(){}

void SmoothGroup::generateNormals(void){
	if(m_has_vn)
		return;
	typedef int VertexID;
	typedef Point3 Normal3;

	map<VertexID, Normal3> vid_normals = map<VertexID,Normal3>();
	map<VertexID, vector<Vertex*>> vid_vertexes = map<VertexID, vector<Vertex*>>();
	for(int t=0;t<m_triangles->size();t++){
		Triangle* triangle = (*m_triangles)[t];
		// Solo calcularlas si no hay normales
		if(!triangle->m_normals){
			Point3 v1 = Point3::getVector(triangle->m_v1.m_v,triangle->m_v2.m_v);
			Point3 v2 = Point3::getVector(triangle->m_v1.m_v,triangle->m_v3.m_v);
			// Producto vectorial
			Normal3 n = v1.crossProduct(v2);
			for(int i=0;i<3;i++){
				Vertex* vx = &triangle->getElement(i);
				if(!vx->m_normal){
					vid_normals[vx->m_vid] = n;
					vid_normals[vx->m_vid].normalize();
					vid_vertexes[vx->m_vid].push_back(vx);
				}
			}
		}
	}
	for(map<int,vector<Vertex*>>::iterator it=vid_vertexes.begin(); it!=vid_vertexes.end(); it++){
		Point3 n = vid_normals[it->first];
		for each (Vertex* vx in it->second){
			vx->m_vn = n;
			vx->m_normal = true;
		}
	}
}

string SmoothGroup::toString(){
	ostringstream output;
	output << "Smooth Group " << m_smoothId << ":" << endl 
	    << "Triangles:" << m_triangles->size();
	return output.str();
}

void SmoothGroup::setTriangles(SmoothGroup::TriangleList* triangles){
	this->m_triangles = triangles;
}

void SmoothGroup::setHasVn(bool has_vn){
	m_has_vn = has_vn;
}

int SmoothGroup::getId(){
	return m_smoothId;
}

void SmoothGroup::setTriangleList(FixedArray<Triangle*>* triangles)
{
	m_triangles = triangles;
}
