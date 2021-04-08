#include <Python.h>

static PyObject *load_map(PyObject* self, PyObject* args)
{   
    char *filename = NULL;
    char * buffer;
    FILE *fp;

    if(!PyArg_ParseTuple(args, "s", &filename)){
        return NULL;
    };
    if(!(fp = fopen(filename, "r"))){
        return NULL;
    };

    fseek(fp , 0 , SEEK_END);
    long lSize = ftell(fp);
    rewind (fp);
    if(!(buffer = (char*) malloc(sizeof(char) * lSize))){
        return NULL;
    };
    size_t result = fread(buffer, 1, lSize, fp);
    if (result != lSize){
        return NULL;
    };
    fclose(fp);
    return 0;
    // return NULL;
    // srand(time(NULL));
    // int const N = 10;
    // PyObject* python_val = PyList_New(N);
    // for (int i = 0; i < N; ++i)
    // {
        // int r = rand() % 10;
        // PyObject* python_int = Py_BuildValue("i", r);
        // PyList_SetItem(python_val, i, python_int);
    // }
    // return python_val;
};

static PyMethodDef RaycasterMethods[] = {
    {"load_map", load_map, METH_VARARGS, "load map"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef raycaster = {
    PyModuleDef_HEAD_INIT,
    "raycaster",
    "Load map and drawing fake 3d view",
    -1,
    RaycasterMethods
};

PyMODINIT_FUNC PyInit_raycaster(void) {
    return PyModule_Create(&raycaster);
};
