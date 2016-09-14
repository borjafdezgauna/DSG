#include "../inc/ObjModel.h"
#include <sstream>
#include <time.h>

ObjModel::ObjModel(void){}

ObjModel::ObjModel(string filename){
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_rx = 0;
	m_ry = 0;
	m_rz = 0;
	m_filename = filename;
	m_name = filename;
	srand(time(NULL));
	for(int i=0,j=2;i<16;i++,j++){
		m_colors[i][0] = 0;//j*0.08;//1.0f *((j ) & 1) + 0.2f;
		m_colors[i][1] = j*0.08;//1.0f *((j >> 1) & 1) + 0.2f;
		m_colors[i][2] = 0;//1.0f *((j >> 2) & 1) + 0.2f;
	}
	m_scale = 0.5f;
}

ObjModel::~ObjModel(void){}

void ObjModel::draw(){
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glRotatef(m_rx,1.0,0,0);
	glRotatef(m_ry,0,1.0,0);
	glRotatef(m_rz,0,0,1.0);
	
	Point3* p1;
	Point3* p2;
	Point3* p3;

	Point3* n1;
	Point3* n2;
	Point3* n3;

	Point3* vt1;
	Point3* vt2;
	Point3* vt3;


	int x = 0;

	//for(Group group: m_textureGroups)
	// Usamos for normal hasta que se pueda usas foreach en la lista

	for (int g=0; g < m_textureGroups->size(); g++)
	{
		//glColor3f(m_colors[g%16][0],m_colors[g%16][1],m_colors[g%16][2]);
		//glColor3f(((float)rand())/32767,((float)rand())/32767,((float)rand())/32767);
		Group* group = m_textureGroups->at(g);
		
		Material* material = group->getMaterial();
		if(material != NULL){
		MaterialTexture* diffuseMaterial = material->m_mapping.m_diffuseMaterial;
			if(diffuseMaterial!=NULL){
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,diffuseMaterial->m_textureId);
				if(diffuseMaterial->m_clamp){
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				}
				else{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				}
			}
		}
		//cout << material->m_color.m_diffuseColor[0] << endl;
		if(material != NULL){
			glMaterialfv(GL_FRONT, GL_AMBIENT, material->m_color.m_ambientColor);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, material->m_color.m_diffuseColor);
			glMaterialfv(GL_FRONT, GL_SPECULAR, material->m_color.m_specularColor);
		}

		//for (Triangle t: group->m_triangles) 
		// Usamos for normal hasta que se pueda usas foreach en la lista
		for (int ti = 0; ti < group->getTriangleList()->size(); ti++)
		{
			Triangle* t = group->getTriangleList()->at(ti);
			
			//glBegin(GL_LINES);
			/*
			glEnable(GL_BLEND);
			glEnable(GL_POLYGON_SMOOTH);*/

			p1 = &(t->m_v1.m_v);
			p2 = &(t->m_v2.m_v);
			p3 = &(t->m_v3.m_v);

			n1 = &(t->m_v1.m_vn);
			n2 = &(t->m_v2.m_vn);
			n3 = &(t->m_v3.m_vn);

			vt1=&(t->m_v1.m_vt);
			vt2=&(t->m_v2.m_vt);
			vt3=&(t->m_v3.m_vt);

			/*
			if(g == 0 && ti == 0){
				cout << "NORMAL: " << ti+1 << " (" << n1->m_x << "," << n1->m_y << "," << n1->m_z << ")" << endl;
			}*/


			

			glBegin(GL_TRIANGLES);
			
			glNormal3f(n1->m_x,n1->m_y,n1->m_z);
			glTexCoord2f(vt1->m_x,vt1->m_y);
			glVertex3f((m_x+p1->m_x)*m_scale,(m_y+p1->m_y)*m_scale,(m_z+p1->m_z)*m_scale);
			glNormal3f(n2->m_x,n2->m_y,n2->m_z);
			glTexCoord2f(vt2->m_x,vt2->m_y);
			glVertex3f((m_x+p2->m_x)*m_scale,(m_y+p2->m_y)*m_scale,(m_z+p2->m_z)*m_scale);
			
			glNormal3f(n3->m_x,n3->m_y,n3->m_z);
			glTexCoord2f(vt3->m_x,vt3->m_y);
			glVertex3f((m_x+p3->m_x)*m_scale,(m_y+p3->m_y)*m_scale,(m_z+p3->m_z)*m_scale);
			glEnd();
			
			//printf("%s ,%f","%s","ANGULO ",angulo ,"\n");

		}
	}

	//glColor3f(0.0f,0.0f,1.0f);

	glPopMatrix();
}

string ObjModel::toString(){
	ostringstream output;
	output << "ObjModel: " << endl << 
		    "Filename: " << m_filename << endl << 
			"Name: " << m_name << endl << 
			"Groups: " << endl;
	for (int i=0;i<m_textureGroups->size();i++){
		output << (*m_textureGroups)[i]->toString();
		if(i!=m_textureGroups->size()-1)
			output << endl;
	}
	return output.str();
	
}

ObjModel& ObjModel::getTestModel()
{
	return ObjModel();
}

void ObjModel::setGroups(GroupList* m_groupList )
{
	m_textureGroups = m_groupList;
}

void ObjModel::rotate(float x, float y,float z)
{
	m_rx+=x;
	m_ry+=y;
	m_rz+=z;
}

void ObjModel::translate(float x, float y,float z)
{
	m_x+=x;
	m_y+=y;
	m_z+=z;
}

void ObjModel::scale(float scaleSize){
	m_scale = scaleSize;
}