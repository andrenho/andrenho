#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include <stdio.h>

Display* display;

static Window find_panel(Window window)
{
	Window panel, w;
	Window* children;
	unsigned int n_children;

	XQueryTree(display, window, &w, &w, &children, &n_children);
	
	int i;
	panel = 0;
	for(i=0; i<n_children; i++)
	{
		Atom strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", 
				False);
		Atom type_return;
		int actual_type;
		unsigned long nitems, bytes;
		unsigned long struts[12] = { 0, };
		int s = XGetWindowProperty(display, window, strut, 0, 12, False, 
				XA_CARDINAL, &type_return, &actual_type,
				&nitems, &bytes, (unsigned char**)&struts);
		if(s == Success)
		{
			if(struts[2] != 0)
				printf("-> %d\n", struts[2]);
			panel = window;
		}
		find_panel(children[i]);
	}

	return panel;
}


int main()
{
	display = XOpenDisplay(NULL);
	Window root = RootWindow(display, DefaultScreen(display));

	printf("%d\n", (int) find_panel(root));

	return 0;
}
