#ifndef Py_PYSTATE_H
#define Py_PYSTATE_H
#ifdef __cplusplus
extern "C" {
#endif

/* Thread and interpreter state structures and their interfaces */


/* State shared between threads */

struct _ts; /* Forward */
struct _is; /* Forward */

typedef struct _is {

	struct _is *next;
	struct _ts *tstate_head;

	PyObject *modules;
	PyObject *sysdict;
	PyObject *builtins;

	int checkinterval;

} PyInterpreterState;


/* State unique per thread */

struct _frame; /* Avoid including frameobject.h */

typedef struct _ts {

	struct _ts *next;
	PyInterpreterState *interp;

	struct _frame *frame;
	int recursion_depth;
	int ticker;
	int tracing;

	PyObject *sys_profilefunc;
	PyObject *sys_tracefunc;

	PyObject *curexc_type;
	PyObject *curexc_value;
	PyObject *curexc_traceback;

	PyObject *exc_type;
	PyObject *exc_value;
	PyObject *exc_traceback;

	PyObject *dict;

	/* XXX signal handlers should also be here */

} PyThreadState;


DL_IMPORT(PyInterpreterState *) PyInterpreterState_New Py_PROTO((void));
DL_IMPORT(void) PyInterpreterState_Clear Py_PROTO((PyInterpreterState *));
DL_IMPORT(void) PyInterpreterState_Delete Py_PROTO((PyInterpreterState *));

DL_IMPORT(PyThreadState *) PyThreadState_New Py_PROTO((PyInterpreterState *));
DL_IMPORT(void) PyThreadState_Clear Py_PROTO((PyThreadState *));
DL_IMPORT(void) PyThreadState_Delete Py_PROTO((PyThreadState *));

DL_IMPORT(PyThreadState *) PyThreadState_Get Py_PROTO((void));
DL_IMPORT(PyThreadState *) PyThreadState_Swap Py_PROTO((PyThreadState *));
DL_IMPORT(PyObject *) PyThreadState_GetDict Py_PROTO((void));


/* Variable and macro for in-line access to current thread state */

extern DL_IMPORT(PyThreadState *) _PyThreadState_Current;

#ifdef Py_DEBUG
#define PyThreadState_GET() PyThreadState_Get()
#else
#define PyThreadState_GET() (_PyThreadState_Current)
#endif

#ifdef __cplusplus
}
#endif
#endif /* !Py_PYSTATE_H */
