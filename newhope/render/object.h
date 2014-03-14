#ifndef RENDER_OBJECT_H_
#define RENDER_OBJECT_H_

class Object {
public:
    Object();

	Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
};

#endif  // RENDER_OBJECT_H_

// vim: ts=4:sw=4:sts=4:expandtab
