#include <ruby.h>

int main(int argc, char** argv)
{
	ruby_init();
	ruby_init_loadpath();

	ruby_eval_string("$: << '../fcca'");
	ruby_eval_string("require 'driver'");
}
