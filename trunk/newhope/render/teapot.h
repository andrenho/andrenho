#ifndef RENDER_TEAPOT_H_
#define RENDER_TEAPOT_H_

class Teapot {
public:
    Teapot();

	Teapot(const Teapot&) = delete;
    Teapot& operator=(const Teapot&) = delete;
};

#endif  // RENDER_TEAPOT_H_

// vim: ts=4:sw=4:sts=4:expandtab
