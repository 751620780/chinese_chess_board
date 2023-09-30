#include <pybind11/pybind11.h>
#include <iostream>
namespace py = pybind11;

int add(int i, int j)
{
    return i + j;
}

class SomeClass
{
    float scale;

public:
    SomeClass(float scale_) : scale(scale_){};
    float multiply(float input)
    {
        float res = scale * input;
        std::cout << "c++ res:" << res << std::endl;
        return res;
    }
};

PYBIND11_MODULE(hello_world, m)
{
    m.doc() = "pybind11 hello_world plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");

    py::class_<SomeClass>(m, "SomeClass","一个浮点乘法器")
        .def("multiply", &SomeClass::multiply)
        .def(py::init<float>());
}