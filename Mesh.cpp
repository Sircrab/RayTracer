//
// Created by Geno on 20-Sep-17.
//

#include "Mesh.h"
#include "AABB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

void Mesh::parse_from_file(const std::string &file, bool computeNormals, const Transform& transform) {
  std::string line;
  std::ifstream meshFile(file);
  while(!meshFile.eof()){
    std::getline(meshFile,line);
    std::string lineType = line.substr(0,2);
    if(lineType == "v "){
      parse_vertex_line(line);
    } else if (lineType == "vt"){
      parse_uv_line(line);
    } else if (lineType == "vn" && !computeNormals){
      parse_normal_line(line);
    } else if (lineType == "f "){
      parse_face_line(line,computeNormals);
    }
  }
  meshFile.close();
  if(computeNormals){
    std::vector<std::vector<unsigned int> > adjacencyList(vertices.size(), std::vector<unsigned int>());
    for(unsigned int i = 0 ; i < triangles.size(); i++){
      adjacencyList[triangles[i].v0].push_back(i);
      adjacencyList[triangles[i].v1].push_back(i);
      adjacencyList[triangles[i].v2].push_back(i);
    }
    for(unsigned int i = 0 ; i < adjacencyList.size(); i++){
      Vec3 calcNormal;
      for(int j = 0; j < adjacencyList[i].size(); j++){
        Triangle curTri = triangles[adjacencyList[i][j]];
        Vec3 A = vertices[curTri.v1] - vertices[curTri.v0];
        Vec3 B = vertices[curTri.v2] - vertices[curTri.v0];
        calcNormal += A.cross(B).normalize();
      }
      normals.push_back(calcNormal.normalize());
    }
  }
  //Apply transform
  for(int i = 0 ; i < vertices.size(); i++){
    vertices[i] = transform.apply(vertices[i]);
  }
  for(int i = 0 ; i < normals.size(); i++){
    normals[i] = transform.apply_normal(normals[i]);
  }
}

void Mesh::parse_vertex_line(const std::string &line) {
  std::istringstream ss(line);
  char filler;
  double v0,v1,v2;
  ss >> filler >> v0 >> v1 >> v2;
  vertices.push_back(Vec3(v0,v1,v2));
}

void Mesh::parse_face_line(const std::string &line, bool computeNormals) {
  Triangle newTri;
  std::stringstream separator;
  std::vector<std::string> faceValues(4);
  separator << line;
  for(int i = 0 ; i < faceValues.size(); i++){
    separator >> faceValues[i];
  }
  unsigned int faceVertices[3];
  unsigned int faceNormals[3];
  unsigned int faceUvs[3] = {0,0,0};
  if(line.find('/') != std::string::npos){
    for(int i = 1; i < 4; i++){
      unsigned int firstSlashPos = faceValues[i].find('/');
      faceVertices[i-1] = std::stoul(faceValues[i].substr(0,firstSlashPos)) - 1;
      unsigned int secondSlashPos = faceValues[i].find('/', firstSlashPos + 1);
      if(secondSlashPos != std::string::npos){
        if((secondSlashPos - firstSlashPos) != 1){
          faceUvs[i-1] = std::stoul(faceValues[i].substr(firstSlashPos + 1, (secondSlashPos - firstSlashPos))) -1;
        }
        faceNormals[i-1] = std::stoul(faceValues[i].substr(secondSlashPos + 1, faceValues[i].size() - secondSlashPos)) - 1;
      } else {
        faceUvs[i-1] = std::stoul(faceValues[i].substr(firstSlashPos + 1, faceValues[i].size() - secondSlashPos)) - 1;
      }
    }
  } else {
    faceVertices[0] = std::stoul(faceValues[1]) - 1;
    faceVertices[1] = std::stoul(faceValues[2]) - 1;
    faceVertices[2] = std::stoul(faceValues[3]) - 1;
    unsigned int normalIdx = normals.size();
    if(!computeNormals){
      Vec3 A = vertices[faceVertices[1]] - vertices[faceVertices[0]];
      Vec3 B = vertices[faceVertices[2]] - vertices[faceVertices[0]];
      normals.push_back(A.cross(B).normalize());
    }
    faceNormals[0] = normalIdx;
    faceNormals[1] = normalIdx;
    faceNormals[2] = normalIdx;
  }
  newTri.v0 = faceVertices[0];
  newTri.v1 = faceVertices[1];
  newTri.v2 = faceVertices[2];
  if(computeNormals){
    newTri.n0 = faceVertices[0];
    newTri.n1 = faceVertices[1];
    newTri.n2 = faceVertices[2];
  } else {
    newTri.n0 = faceNormals[0];
    newTri.n1 = faceNormals[1];
    newTri.n2 = faceNormals[2];
  }
  newTri.uv0 = faceUvs[0];
  newTri.uv1 = faceUvs[1];
  newTri.uv2 = faceUvs[2];
  triangles.push_back(newTri);
}

void Mesh::parse_uv_line(const std::string &line) {
  std::istringstream ss(line);
  std::string filler;
  double vt0, vt1;
  ss >> filler >> vt0 >> vt1;
  uvs.push_back(Vec2(vt0,vt1));
}

void Mesh::parse_normal_line(const std::string &line) {
  std::istringstream ss(line);
  std::string filler;
  double vn0, vn1, vn2;
  ss >> filler >> vn0 >> vn1 >> vn2;
  normals.push_back(Vec3(vn0,vn1,vn2).normalize());
}

AABB Mesh::calc_AABB() {
  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();;
  double minZ = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::min();
  double maxY = std::numeric_limits<double>::min();
  double maxZ = std::numeric_limits<double>::min();
  for(auto& vert : vertices){
    minX = std::min(minX,vert.x);
    minY = std::min(minY, vert.y);
    minZ = std::min(minZ, vert.z);
    maxX = std::max(maxX, vert.x);
    maxY = std::max(maxY, vert.y);
    maxZ = std::max(maxZ, vert.z);
  }
  return AABB(Vec3(minX,minY,minZ),Vec3(maxX,maxY,maxZ));
}