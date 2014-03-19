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
OBJ_Loader::Load(string const& filename, Object& obj)
{
    ifstream in(filename);
    if(in.is_open()) {
        string cmd;
        while(in >> cmd) {
            if(!cmd.empty()) {
                if(cmd[0] == '#' || cmd == "o" || cmd == "s" || cmd == "vt" || cmd == "g") {
                    getline(in, cmd);
                } else if(cmd == "v") { // vertice
                    float x, y, z;
                    in >> x >> y >> z;
                    obj.vertices.emplace_back(x, y, z);
                } else if(cmd == "vn") { // normal vertice
                    float x, y, z;
                    in >> x >> y >> z;
                    obj.normal_vertices.emplace_back(x, y, z);
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
                    }
                    obj.triangles.emplace_back(triangle);
                    obj.normals.emplace_back(normal);
                } else {
                    throw "Invalid command '" + cmd + "' on file " + filename;
                }
            }
        }
    } else {
        throw "Could not open file " + filename;
    }
}


vector<string> 
OBJ_Loader::Split(string const& s, char delim, vector<string>& elems)
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
