#ifndef PYFMATH
#define PYFMATH
#ifdef __cplusplus
extern "C" {
#endif
#include "Python.h"
#define add_name(func) #func, _##func
#define parse(arg) (*(long long*)_parse(PyFloat_AS_DOUBLE(arg)))
#define parsed parse(args)
#define _declare(func, value, ...) const static inline PyObject * func(__VA_ARGS__) {return value;}
#define declare(func, operation, type) _declare(_##func, Py##type##_FromLong(operation), const PyObject * self, const PyObject * args)
const long long one = 0x3FF0000000000000;
const static inline void * _parse(const double arg){return & arg;}
_declare(PyFloat_FromLong, PyFloat_FromDouble(*(double*)&x), const long long x);
declare(abs, parsed & INT64_MAX, Float);
declare(sign, ~parsed >> 0x3F, Bool);
declare(sqrt, (parsed >> 1) + (one >> 1), Float);
_declare(_log2, PyFloat_FromDouble((double)(parsed >> 0x17) - 126.4), const PyObject * self, const PyObject * args);
_declare(_pow, PyFloat_FromLong((parse(args[0]) - one) * PyFloat_AS_DOUBLE(args[1]) + one), const PyObject * self, const PyObject *const *args, const Py_ssize_t nargs);
const static inline PyObject *_min(const PyObject * self, const PyObject *const *args, const Py_ssize_t nargs) {
    long long m = parse(args[0]), cur;
    for (int i = 1; i < nargs; cur = parse(args[i++]))
        m ^= (cur ^ m) & -(*(double*)cur < *(double*)m);
    return PyFloat_FromLong(m);
}
const static inline PyObject *_max(const PyObject * self, const PyObject *const *args, const Py_ssize_t nargs) {
    long long m = parse(args[0]), cur;
    for (int i = 1; i < nargs; cur = parse(args[i++]))
        m ^= (cur ^ m) & -(*(double*)cur > *(double*)m);
    return PyFloat_FromLong(m);
}
static PyMethodDef fmath_methods[] = {
    {add_name(pow), METH_FASTCALL, "pow: return x to the power of y"},
    {add_name(min), METH_FASTCALL, "min: get the minimum value of a list"},
    {add_name(max), METH_FASTCALL, "max: get the maximum value of a list"},
    {add_name(abs), METH_O, "abs: return the absolute value of x"},
    {add_name(sign), METH_O, "sign: return True if x>=0 else False"},
    {add_name(log2), METH_O, "log2: return the log base 2 of x"},
    {add_name(sqrt), METH_O, "sqrt: return the square root of x"},
    {NULL, NULL, 0, NULL}
};
static struct PyModuleDef pyfmath_module = {PyModuleDef_HEAD_INIT, "fmath", NULL, -1, fmath_methods};
PyMODINIT_FUNC PyInit_fmath(void){return PyModule_Create(&pyfmath_module);}
#ifdef __cplusplus
}
#endif
#endif
