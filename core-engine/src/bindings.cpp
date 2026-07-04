#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "noncommutative.hpp"
#include "eigen_solver.hpp"

namespace py = pybind11;
using namespace PseudoParadox;

PYBIND11_MODULE(pseudo_paradox_core, m) {
    m.doc() = "Pseudo-Paradox C++ High-Speed Noncommutative Math Core Engine";

    // Bind the QuantumOperator Class to Python
    py::class_<QuantumOperator>(m, "QuantumOperator")
        .def(py::init<int>(), py::arg("dimension")) // Expose baseline constructor
        .def(py::init<int, const QuantumMatrix&>(), py::arg("dimension"), py::arg("matrix"))
        
        // Expose overloaded operator metrics
        .def("__add__", &QuantumOperator::operator+)
        .def("__sub__", &QuantumOperator::operator-)
        .def("__mul__", [](const QuantumOperator& a, const QuantumOperator& b) { return a * b; })
        .def("__mul__", [](const QuantumOperator& a, const Complexd& s) { return a * s; })
        
        // Expose helper checks
        .def("is_hermitian", &QuantumOperator::is_hermitian, py::arg("epsilon") = 1e-9)
        .def("commutes_with", &QuantumOperator::commutes_with, py::arg("other"), py::arg("epsilon") = 1e-9)
        .def_static("commutator", &QuantumOperator::commutator, "Computes [A, B] = AB - BA")
        .def_property_readonly("dimension", &QuantumOperator::get_dimension);

    // Bind the Stateless Numerical EigenSolver Utility functions
    py::class_<EigenSolver>(m, "EigenSolver")
        .def_static("solve_spectrum", &EigenSolver::solve_spectrum, "Extracts flat real eigenvalues")
        .def_static("solve_eigenvectors", &EigenSolver::solve_eigenvectors)
        .def_static("compute_trace", &EigenSolver::compute_trace);
}
