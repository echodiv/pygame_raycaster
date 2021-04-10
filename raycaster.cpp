#include <Python.h>
#include <string>

using namespace std;

static PyObject *load_map(PyObject* self, PyObject* args)
{   
    char *fileName = NULL;
    int mapWidth = 0;
    bool knowMapWidth = false;
    string mapInString;

    if(!PyArg_ParseTuple(args, "s", &fileName)){
        return NULL;
    };
    
    FILE *mapFile;
    if(!(mapFile = fopen(fileName, "rb"))){
        return NULL;
    };
    fseek(mapFile, 0, SEEK_END);
    size_t size = ftell(mapFile);
    
    mapInString.resize(size);
    rewind(mapFile);
    fread(&mapInString[0], 1, size, mapFile);
    fclose(mapFile);

    PyObject* python_val = PyList_New(0);
    PyObject* python_ins = PyList_New(0);
    int i = 0;

    for(auto symbol: mapInString){
        if(symbol != '\n'){
            PyObject* python_int = Py_BuildValue("i", symbol - '0');
            PyList_Append(python_ins, python_int);
            if (!knowMapWidth) ++mapWidth;
        }
        else{
            PyList_Append(python_val, PyList_GetSlice(python_ins, i*mapWidth, (i+1)*mapWidth));
            ++i;
            knowMapWidth = true;
        }
    }
    return python_val;

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
