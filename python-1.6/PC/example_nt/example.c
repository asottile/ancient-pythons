#include "Python.h"

static PyObject *
ex_foo(self, args)
	PyObject *self, *args;
{
	printf("Hello, world\n");
	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef example_methods[] = {
	{"foo", ex_foo, 1, "foo() doc string"},
	{NULL, NULL}
};

void
initexample()
{
	Py_InitModule("example", example_methods);
}
