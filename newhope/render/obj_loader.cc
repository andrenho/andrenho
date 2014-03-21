#include "obj_loader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "render/object.h"

namespace render {

void
OBJ_Loader::Load(string const& filename, vector<struct Vertice>& vertices)
{
    glm::vec3 current_color = { 1, 1, 1 };
    ifstream in(filename);
    if(in.is_open()) {
        string cmd;
        while(in >> cmd) {
            if(!cmd.empty()) {
                if(cmd[0] == '#' || cmd == "o" || cmd == "s" || cmd == "vt" || cmd == "g") {
                    getline(in, cmd);
                } else if(cmd == "mtllib") {
                    string file;
                    in >> file;
                    LoadMaterials("data/" + file); // TODO
                } else if(cmd == "usemtl") {
                    string material;
                    in >> material;
                    try {
                        current_color = colors.at(material);
                    } catch(out_of_range& e) {
                        throw "Invalid color " + material;
                    }
                } else if(cmd == "v") { // vertice
                    float x, y, z;
                    in >> x >> y >> z;
                    points.emplace_back(x, y, z);
                } else if(cmd == "vn") { // normal vertice
                    float x, y, z;
                    in >> x >> y >> z;
                    normals.emplace_back(x, y, z);
                } else if(cmd == "f") { // triangles
                    vector<string> elements;
                    array<int,3> triangle, normal;
                    string vect[3];
                    in >> vect[0] >> vect[1] >> vect[2];
                    for(int i=0; i<3; i++) {
                        elements.clear();
                        Split(vect[i], '/', elements);
                        triangle[i] = atoi(elements[0].c_str());
                        normal[i] = atoi(elements[2].c_str());

                        vertices.push_back({
                                { points[triangle[i]-1].x, points[triangle[i]-1].y, points[triangle[i]-1].z, },
                                { normals[normal[i]-1].x, normals[normal[i]-1].y, normals[normal[i]-1].z, }, 
                                current_color
                        });
                    }
                } else {
                    throw "Invalid command '" + cmd + "' on file " + filename;
                }
            }
        }
    } else {
        throw "Could not open file " + filename;
    }
}


void 
OBJ_Loader::LoadMaterials(string const& filename)
{
    string current = "";
    ifstream in(filename);
    if(in.is_open()) {
        string cmd;
        while(in >> cmd) {
            if(!cmd.empty()) {
                if(cmd == "newmtl") {
                    in >> current;
                } else if(cmd == "Kd") {
                    if(current == "") {
                        throw "Kd without newmtl in " + filename;
                    }
                    float r, g, b;
                    in >> r >> g >> b;
                    colors[current] = { r, g, b };
                } else {
                    getline(in, cmd);
                }
            }
        }
    } else {
        throw "Could not open file " + filename;
    }
}


vector<string> 
OBJ_Loader::Split(string const& s, char delim, vector<string>& elems) const
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


}

// vim: ts=4:sw=4:sts=4:expandtab
