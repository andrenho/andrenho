// code by Markus Koenig

#include <stdlib.h>
#include <curses.h>
#include <ruby.h>

/*
 * Curses#define_acs
 * Add the ACS constants to Curses.
 */
VALUE curses_define_acs(VALUE self) {
        rb_define_const(self, "ACS_BLOCK", ULONG2NUM(ACS_BLOCK));
        rb_define_const(self, "ACS_BOARD", ULONG2NUM(ACS_BOARD));
        rb_define_const(self, "ACS_BTEE", ULONG2NUM(ACS_BTEE));
        rb_define_const(self, "ACS_BULLET", ULONG2NUM(ACS_BULLET));
        rb_define_const(self, "ACS_CKBOARD", ULONG2NUM(ACS_CKBOARD));
        rb_define_const(self, "ACS_DARROW", ULONG2NUM(ACS_DARROW));
        rb_define_const(self, "ACS_DEGREE", ULONG2NUM(ACS_DEGREE));
        rb_define_const(self, "ACS_DIAMOND", ULONG2NUM(ACS_DIAMOND));
        rb_define_const(self, "ACS_GEQUAL", ULONG2NUM(ACS_GEQUAL));
        rb_define_const(self, "ACS_HLINE", ULONG2NUM(ACS_HLINE));
        rb_define_const(self, "ACS_LANTERN", ULONG2NUM(ACS_LANTERN));
        rb_define_const(self, "ACS_LARROW", ULONG2NUM(ACS_LARROW));
        rb_define_const(self, "ACS_LEQUAL", ULONG2NUM(ACS_LEQUAL));
        rb_define_const(self, "ACS_LLCORNER", ULONG2NUM(ACS_LLCORNER));
        rb_define_const(self, "ACS_LRCORNER", ULONG2NUM(ACS_LRCORNER));
        rb_define_const(self, "ACS_LTEE", ULONG2NUM(ACS_LTEE));
        rb_define_const(self, "ACS_NEQUAL", ULONG2NUM(ACS_NEQUAL));
        rb_define_const(self, "ACS_PI", ULONG2NUM(ACS_PI));
        rb_define_const(self, "ACS_PLMINUS", ULONG2NUM(ACS_PLMINUS));
        rb_define_const(self, "ACS_PLUS", ULONG2NUM(ACS_PLUS));
        rb_define_const(self, "ACS_RARROW", ULONG2NUM(ACS_RARROW));
        rb_define_const(self, "ACS_RTEE", ULONG2NUM(ACS_RTEE));
        rb_define_const(self, "ACS_S1", ULONG2NUM(ACS_S1));
        rb_define_const(self, "ACS_S3", ULONG2NUM(ACS_S3));
        rb_define_const(self, "ACS_S7", ULONG2NUM(ACS_S7));
        rb_define_const(self, "ACS_S9", ULONG2NUM(ACS_S9));
        rb_define_const(self, "ACS_STERLING", ULONG2NUM(ACS_STERLING));
        rb_define_const(self, "ACS_TTEE", ULONG2NUM(ACS_TTEE));
        rb_define_const(self, "ACS_UARROW", ULONG2NUM(ACS_UARROW));
        rb_define_const(self, "ACS_ULCORNER", ULONG2NUM(ACS_ULCORNER));
        rb_define_const(self, "ACS_URCORNER", ULONG2NUM(ACS_URCORNER));
        rb_define_const(self, "ACS_VLINE", ULONG2NUM(ACS_VLINE));
        return Qnil;
}

/*
 * Curses#addch_gen
 * addch for generic char values (Curses#addch truncates to 8 bit)
 */
static VALUE curses_addch_gen(VALUE self, VALUE c) {
        addch(NUM2ULONG(c));
        return Qnil;
}

/* This is called upon extension loading. */
void Init_curses_acs(void) {
        VALUE curses_cls;
        rb_require("curses");
        curses_cls = rb_eval_string("Curses");
        rb_define_singleton_method(curses_cls, "define_acs",
                curses_define_acs, 0);
        rb_define_singleton_method(curses_cls, "addch_gen",
                curses_addch_gen, 1);
}

