#ifndef EVENT_H
#define EVENT_H

struct UI;
struct World;

void evt_process(struct UI* event, struct World* world);

#endif
