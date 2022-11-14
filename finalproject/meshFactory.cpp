#pragma once
#include "MeshFactory.h"
#include <windows.h>
#include "ObjMesh.h"

void CMeshFacotry::LoadObjModel(char* fileDir, ObjMesh* mesh)
{
	FILE* fp = fopen(fileDir, "r");
	if (fp == NULL) {
		printf("%s file can not open", fileDir);
		exit(1);
	}
	int numVertex = 0;
	int numFaces = 0;
	int numNormals = 0;
	int numTexcoords = 0;

	float* vertices = NULL;
	float* normals = NULL;
	int* faces = NULL;
	int* textureFace = NULL;
	float* texCoords = NULL;

	char line[256];

	while (!feof(fp)) {
		fgets(line, 256, fp);
		if (line[0] == 'v') {
			if (line[1] == 't') {			//texture
				numTexcoords++;
			}
			else if (line[1] == 'n') {	//normal
			}
			else if (line[1] == ' ')		//vertex
				numVertex++;
		}
		else if (line[0] == 'f') {		//face
			numFaces++;
		}
	}
	rewind(fp);

	printf("number of vertices : %d\n", numVertex);
	printf("number of indices : %d\n", numFaces);

	vertices = (float*)malloc(sizeof(float) * 3 * numVertex);		//���� 
	texCoords = (float*)malloc(sizeof(float) * 2 * numTexcoords);	//�ؽ��� 
	faces = (int*)malloc(sizeof(int) * 3 * numFaces);				//�� (����)
	textureFace = (int*)malloc(sizeof(int) * 3 * numFaces);			//�� (�ؽ���)

	int j = 0, k = 0;
	int IdxFace = 0;
	int IdxTexCoord = 0;

	while (!feof(fp)) {
		fgets(line, 256, fp);
		if (line[0] == 'v') {				//������ �б�// vt�� �ؽ��� ���� 
			if (line[1] == 't') {			//texture
											//////////////////////////////////////////////////////////////////////////
											//�ؽ��� �ε�
											//////////////////////////////////////////////////////////////////////////
			}
			else if (line[1] == 'n') {	//normal
			}
			else {						//vertex
				fseek(fp, -(strlen(line) + 1), SEEK_CUR);		//���� ������

				float x, y, z;
				fscanf(fp, "%s %f %f %f", line, &x, &y, &z);
				vertices[j++] = x;	vertices[j++] = y;	vertices[j++] = z;
				//printf("%f %f %f\n", vertices[j-3], vertices[j-2], vertices[j-1]);
			}
		}
		else if (line[0] == 'f') {		//������ �б�
			if (numTexcoords > 0) {		//Obj �ؽ��İ� ������ "/" �����ڸ� ���� �ؾ� ��
				for (int i = 0; i < strlen(line); ++i) {
					if (line[i] == '/')	line[i] = ' ';
				}

				char* token;
				token = strtok(line, " ");	//token�� line���ڿ��� ���� �������� �и��� ����� ���� "f 1212 1212 2323 2323 4343 4343"

				int p1 = atoi(strtok(NULL, " ")), t1 = atoi(strtok(NULL, " "));
				int p2 = atoi(strtok(NULL, " ")), t2 = atoi(strtok(NULL, " "));
				int p3 = atoi(strtok(NULL, " ")), t3 = atoi(strtok(NULL, " "));

				//���� ���� ���� ����
				faces[IdxFace++] = p1 - 1;			faces[IdxFace++] = p2 - 1;			faces[IdxFace++] = p3 - 1;
				//���� �ؽ��� ���� ����
				textureFace[IdxTexCoord++] = t1 - 1;	textureFace[IdxTexCoord++] = t2 - 1;	textureFace[IdxTexCoord++] = t3 - 1;

				//printf("%d %d %d %d %d %d\n", p1, t1, p2, t2, p3, t3);
			}
			else {						//�ؽ��İ� ���� �� ����
				int f1, f2, f3;
				fseek(fp, -(strlen(line) + 1), SEEK_CUR);		//���� ������
				fscanf(fp, "%s %d %d %d", line, &f1, &f2, &f3);		//Obj �ؽ��İ� ������ 3���� �������� ���� 
				faces[k++] = f1 - 1;	faces[k++] = f2 - 1;	faces[k++] = f3 - 1;
				//printf("%d %d %d\n", faces[j-3], faces[j-2], faces[j-1]);
			}
		}
	}

	//����
	mesh->m_numVertices = numVertex;
	mesh->m_vertices = vertices;

	//�ؽ��� 
	mesh->m_numTexCoords = numTexcoords;
	mesh->m_texCoords = texCoords;

	//������, ����, �ؽ��� ����
	mesh->m_numFaces = numFaces;
	mesh->m_TextureFace = textureFace;
	mesh->m_Faces = faces;

	//�븻
}
