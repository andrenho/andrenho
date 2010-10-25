#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

Display* display;

// looks for the maximum "docking height" of all children of this window
static int top_panel_height(Window window)
{
	int height = 0;		// maximum height
	Window w;
	Window* children;
	unsigned int n_children;

	XQueryTree(display, window, &w, &w, &children, &n_children);
	
	// looks for each one of the children
	int i;
	for(i=0; i<n_children; i++)
	{
		// this is the property we're looking for
		Atom strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", 
				False);
		Atom type_return;
		int actual_type;
		unsigned long nitems, bytes;
		unsigned char* data = NULL;
		
		// load window attributes (we only want to know about the
		//                         windows where y = 0)
		XWindowAttributes xwa;
		XGetWindowAttributes(display, window, &xwa);

		// load the property _NET_WM_STRUT_PARTIAL
		int s = XGetWindowProperty(display, window, strut, 0, LONG_MAX, 
				False, 
				XA_CARDINAL, &type_return, &actual_type,
				&nitems, &bytes, (unsigned char**)&data);
		if(s == Success)
		{
			Atom *state = (Atom *) data;
			// state[2] contains the "dock height"
			if(xwa.y == 0 && nitems > 0 && state[2])
				if(state[2] > height)
					height = state[2];
		}

		// recursively, traverse the tree of all children of children
		int children_max_height = top_panel_height(children[i]);
		if(children_max_height > height)
			height = children_max_height;
	}

	return height;
}


int main()
{
	display = XOpenDisplay(NULL);
	Window root = RootWindow(display, DefaultScreen(display));

	printf("%d\n", top_panel_height(root));

	return 0;
}
