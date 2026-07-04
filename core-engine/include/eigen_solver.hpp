#ifndef PSEUDO_PARADOX_EIGEN_SOLVER_HPP
#define PSEUDO_PARADOX_EIGEN_SOLVER_HPP

#include "noncommutative.hpp"
#include <vector>

namespace PseudoParadox {

    class EigenSolver {
    public:
        // Pure stateless static mathematical utility structures
        EigenSolver() = delete;
        ~EigenSolver() = delete;

        /**
         * Extract raw, sorted real-valued eigenvalues from a QuantumOperator.
         * These directly modulate the physical shapes in our 3D world mesh.
         */
        static std::vector<double> solve_spectrum(const QuantumOperator& op);

        /**
         * Extract the full spatial matrix representation of the eigenflow trajectories.
         */
        static QuantumMatrix solve_eigenvectors(const QuantumOperator& op);

        /**
         * Evaluates the trace of the operator to confirm conservation boundaries.
         */
        static Complexd compute_trace(const QuantumOperator& op);
    };

} // namespace PseudoParadox

#endif // PSEUDO_PARADOX_EIGEN_SOLVER_HPP
