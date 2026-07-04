cd ~/Pseudo-Paradox

cat << 'EOF' > core-engine/include/eigen_solver.hpp
#ifndef PSEUDO_PARADOX_EIGEN_SOLVER_HPP
#define PSEUDO_PARADOX_EIGEN_SOLVER_HPP

#include "noncommutative.hpp"
#include <vector>

namespace PseudoParadox {

    class EigenSolver {
    public:
        // Delete constructor to enforce pure, stateless static utility methods
        EigenSolver() = delete;
        ~EigenSolver() = delete;

        /**
         * Extract raw, sorted real-valued eigenvalues from a QuantumOperator.
         * Throws a runtime error if the underlying operator violates Hermitian symmetry.
         * These outputs directly modulate the height metrics of your 3D world mesh.
         */
        static std::vector<double> solve_spectrum(const QuantumOperator& op);

        /**
         * Extract the full spatial matrix representation of the eigenflow trajectories.
         * Maps out how state trajectories morph under continuous transformation parameters.
         */
        static QuantumMatrix solve_eigenvectors(const QuantumOperator& op);

        /**
         * Evaluates the trace of the operator (sum of its eigenvalues).
         * Used to confirm state preservation and trace-class normalization boundaries.
         */
        static Complexd compute_trace(const QuantumOperator& op);
    };

} // namespace PseudoParadox

#endif // PSEUDO_PARADOX_EIGEN_SOLVER_HPP
EOF
