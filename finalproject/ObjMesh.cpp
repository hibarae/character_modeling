// ObjMesh.cpp: implementation of the ObjMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "ObjMesh.h"
#include <STDIO.H>
#include <stdlib.h>
#include <gl/glut.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ObjMesh::ObjMesh()
{
	m_vertices = NULL;
	m_texCoords = NULL;
	m_normals = NULL;

	m_Faces = NULL;
	m_TextureFace = NULL;

	m_numTexCoords = m_numVertices = m_numFaces = m_numNormals = 0;

	m_Color[0] = 1;
	m_Color[1] = 1;
	m_Color[2] = 1;
}

ObjMesh::~ObjMesh()
{
	// 	if(m_vertices != NULL)
	// 		free(m_vertices);
	// 	if(m_normals != NULL)
	// 		free(m_normals);
	// 	if(m_Faces != NULL)
	// 		free(m_Faces);
	// 	if(m_texCoords != NULL)
	// 		free(m_texCoords);
	// 	if(m_TextureFace != NULL)
	// 		free(m_TextureFace);
	// 	if(m_TextureID != -1)
	// 		glDeleteTextures(1, &m_TextureID);
}

void ObjMesh::Render()
{
	glPushMatrix();

	//면 그리기
	glColor3fv(m_Color);
	float j = 0;
	for (int i = 0; i < m_numFaces * 3; i += 3)
	{
		glBegin(GL_TRIANGLES);
		float p1[3] = { m_vertices[m_Faces[i + 0] * 3 + 0], m_vertices[m_Faces[i + 0] * 3 + 1], m_vertices[m_Faces[i + 0] * 3 + 2] };
		float p2[3] = { m_vertices[m_Faces[i + 1] * 3 + 0], m_vertices[m_Faces[i + 1] * 3 + 1], m_vertices[m_Faces[i + 1] * 3 + 2] };
		float p3[3] = { m_vertices[m_Faces[i + 2] * 3 + 0], m_vertices[m_Faces[i + 2] * 3 + 1], m_vertices[m_Faces[i + 2] * 3 + 2] };

		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);

		glEnd();
	}

	//외곽선 그리기
	glScalef(1.0001, 1.0001, 1.0001);
	glColor3d(0, 0, 0);
	for (int i = 0; i < m_numFaces * 3; i += 3)
	{
		glBegin(GL_LINES);
		glVertex3f(m_vertices[m_Faces[i + 0] * 3 + 0], m_vertices[m_Faces[i + 0] * 3 + 1], m_vertices[m_Faces[i + 0] * 3 + 2]);
		glVertex3f(m_vertices[m_Faces[i + 1] * 3 + 0], m_vertices[m_Faces[i + 1] * 3 + 1], m_vertices[m_Faces[i + 1] * 3 + 2]);

		glVertex3f(m_vertices[m_Faces[i + 1] * 3 + 0], m_vertices[m_Faces[i + 1] * 3 + 1], m_vertices[m_Faces[i + 1] * 3 + 2]);
		glVertex3f(m_vertices[m_Faces[i + 2] * 3 + 0], m_vertices[m_Faces[i + 2] * 3 + 1], m_vertices[m_Faces[i + 2] * 3 + 2]);

		glVertex3f(m_vertices[m_Faces[i + 2] * 3 + 0], m_vertices[m_Faces[i + 2] * 3 + 1], m_vertices[m_Faces[i + 2] * 3 + 2]);
		glVertex3f(m_vertices[m_Faces[i + 0] * 3 + 0], m_vertices[m_Faces[i + 0] * 3 + 1], m_vertices[m_Faces[i + 0] * 3 + 2]);
		glEnd();
	}

	glPopMatrix();
}

void ObjMesh::SetColor(float r, float g, float b)
{
	m_Color[0] = r;
	m_Color[1] = g;
	m_Color[2] = b;
}

