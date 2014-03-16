#include "render/obj_object.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace render {

OBJ_Object::OBJ_Object(string const& filename)
{
    LoadOBJ(filename);
    SetupObject();
}

void 
OBJ_Object::LoadOBJ(string const& filename)
{
    ifstream in(filename);
    if(in.is_open()) {
        string cmd;
        while(in >> cmd) {
            if(!cmd.empty()) {
                if(cmd[0] == '#' || cmd == "o" || cmd == "s" || cmd == "vn") {
                    getline(in, cmd);
                } else if(cmd == "v") { // vertice
                    float x, y, z;
                    in >> x >> y >> z;
                    vertices.emplace_back(x, y, z);
                } else if(cmd == "f") {
                    vector<string> elements;
                    array<int,3> triangle;
                    string vect[3];
                    in >> vect[0] >> vect[1] >> vect[2];
                    for(int i=0; i<3; i++) {
                        elements.clear();
                        Split(vect[i], '/', elements);
                        triangle[i] = stoi(elements[0]);
                    }
                    triangles.emplace_back(triangle);
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
OBJ_Object::SetupObject()
{
    // setup program
    program = SetupProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    // initialize VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // initialize VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // upload data to graphic card
    int i=0;
    GLfloat* vertex = new GLfloat[triangles.size()*9];
    for(auto const& triangle: triangles) {
        for(int j=0; j<3; j++) {
            glm::vec3& vertice = vertices[triangle[j]-1];
            vertex[i++] = vertice.x;
            vertex[i++] = vertice.y;
            vertex[i++] = vertice.z;
        }
    }
    for(int i=0; i<triangles.size()*9; i+=3) {
        cout << vertex[i] << " " << vertex[i+1] << " " << vertex[i+2] <<  endl;
    }
    glBufferData(GL_ARRAY_BUFFER, triangles.size() * 9, vertex, GL_STATIC_DRAW);
    delete vertex;

    // link program variables
    GLint vert = glGetAttribLocation(program, "vert");
    glVertexAttribPointer(vert, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vert);

    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


vector<string> 
OBJ_Object::Split(string const& s, char delim, vector<string>& elems) const
{
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


void 
OBJ_Object::Render() const
{
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(triangles.size() * 9));
}


}

// vim: ts=4:sw=4:sts=4:expandtab
