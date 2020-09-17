#include <stdio.h>
#include <Python.h>
typedef unsigned long int uint64_t;
//gcc -shared  hanming.c -o hanming.so
// bit population count, see
// http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel

int hanming(uint64_t v1,  uint64_t  v2)
{
     uint64_t out = v1 ^ v2;
     out -= (out >> 1) & 0x5555555555555555;
     out = (0x3333333333333333 & out) + (0x3333333333333333 & (out >> 2));
     out = (out + (out >> 4)) & 0x0f0f0f0f0f0f0f0f;
     out &= 0x0f0f0f0f0f0f0f0f;
	 out *= 0x0101010101010101;
     return out >> 56;
}

static PyObject* hanming_distance(PyObject* self, PyObject* args) {
    PyObject *result = NULL;
    uint64_t v1, v2;
    if (PyArg_ParseTuple(args, "LL", &v1, &v2) ) {
        result = Py_BuildValue("i", hanming(v1, v2));
    }
    return result;
}

static char hanming_docs[] =
    "provides fast hanming distance calculation";


static PyMethodDef hanming_module_methods[] = {
    {"hanming_distance", (PyCFunction)hanming_distance,
     METH_VARARGS, hanming_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef hanming_module_definition = {
    PyModuleDef_HEAD_INIT,
    "hanming",
    "Extension module that provides hanming distance calculation function",
    -1,
    hanming_module_methods
};


PyMODINIT_FUNC PyInit_hanming(void) {
    Py_Initialize();
    return PyModule_Create(&hanming_module_definition);
}