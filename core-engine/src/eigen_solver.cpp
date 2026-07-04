cd ~/Pseudo-Paradox

cat << 'EOF' > core-engine/src/eigen_solver.cpp
#include "eigen_solver.hpp"
#include <stdexcept>

namespace PseudoParadox {

    // ==============================================================================
    // NUMERICAL SPECTRUM SOLVER OPERATIONS
    // ==============================================================================

    std::vector<double> EigenSolver::solve_spectrum(const QuantumOperator& op) {
        // Guard rail check: Ensure operator is self-adjoint to guarantee real eigenvalues
        if (!op.is_hermitian()) {
            throw std::runtime_error("// SOLVER FATAL: OPERATOR VIOLATES HERMITIAN SYMMETRIC MATRIX RULES //");
        }

        const auto& raw_matrix = op.get_raw_matrix();
        
        // Eigen::SelfAdjointEigenSolver is deeply optimized for computing real spectrum data
        Eigen::SelfAdjointEigenSolver<QuantumMatrix> solver(raw_matrix);
        
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("// SOLVER ERROR: SPECTRAL NUMERICAL CONVERGENCE FAILURE //");
        }

        // Extract the raw real eigenvalues and map them to a native C++ flat vector
        const auto& eigenvalues = solver.eigenvalues();
        std::vector<double> spectrum(eigenvalues.data(), eigenvalues.data() + eigenvalues.size());
        
        return spectrum;
    }

    QuantumMatrix EigenSolver::solve_eigenvectors(const QuantumOperator& op) {
        if (!op.is_hermitian()) {
            throw std::runtime_error("// SOLVER FATAL: CANNOT CALCULATE EIGENVECTORS OF NON-HERMITIAN OPERATOR //");
        }

        Eigen::SelfAdjointEigenSolver<QuantumMatrix> solver(op.get_raw_matrix());
        
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("// SOLVER ERROR: EIGENVECTOR SPECTRAL CONVERGENCE FAILURE //");
        }

        // Returns a dense matrix where column (i) corresponds to the i-th eigenvalue's state trajectory
        return solver.eigenvectors();
    }

    Complexd EigenSolver::compute_trace(const QuantumOperator& op) {
        // The mathematical matrix trace is the exact sum of all elements along the primary diagonal
        return op.get_raw_matrix().trace();
    }

} // namespace PseudoParadox
EOF
