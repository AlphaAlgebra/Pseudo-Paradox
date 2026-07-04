cd ~/Pseudo-Paradox

cat << 'EOF' > core-engine/src/noncommutative.cpp
#include "noncommutative.hpp"
#include <stdexcept>

namespace PseudoParadox {

    // ==============================================================================
    // CONSTRUCTORS & LIFECYCLE MANAGEMENT
    // ==============================================================================
    
    // Initialize an empty operator matrix populated with zero values
    QuantumOperator::QuantumOperator(int dimension)
        : dimension_(dimension), matrix_(QuantumMatrix::Zero(dimension, dimension)) {
        if (dimension <= 0) {
            throw std::invalid_argument("// MATH ERROR: OPERATOR DIMENSION MUST BE POSITIVE //");
        }
    }

    // Initialize an operator directly with an existing Eigen matrix template
    QuantumOperator::QuantumOperator(int dimension, const QuantumMatrix& initial_matrix)
        : dimension_(dimension), matrix_(initial_matrix) {
        if (dimension <= 0) {
            throw std::invalid_argument("// MATH ERROR: OPERATOR DIMENSION MUST BE POSITIVE //");
        }
        if (initial_matrix.rows() != dimension || initial_matrix.cols() != dimension) {
            throw std::invalid_argument("// MATH ERROR: INITIAL MATRIX MATRIX BOUNDS MISMATCH //");
        }
    }

    // ==============================================================================
    // OVERLOADED MATHEMATICAL ARITHMETIC OPERATORS
    // ==============================================================================

    QuantumOperator QuantumOperator::operator+(const QuantumOperator& other) const {
        if (this->dimension_ != other.dimension_) {
            throw std::invalid_argument("// ALGEBRA DIMENSION MISMATCH DURING OPERATOR ADDITION //");
        }
        return QuantumOperator(dimension_, this->matrix_ + other.matrix_);
    }

    QuantumOperator QuantumOperator::operator-(const QuantumOperator& other) const {
        if (this->dimension_ != other.dimension_) {
            throw std::invalid_argument("// ALGEBRA DIMENSION MISMATCH DURING OPERATOR SUBTRACTION //");
        }
        return QuantumOperator(dimension_, this->matrix_ - other.matrix_);
    }

    // High-speed matrix multiplication layer (AB)
    QuantumOperator QuantumOperator::operator*(const QuantumOperator& other) const {
        if (this->dimension_ != other.dimension_) {
            throw std::invalid_argument("// ALGEBRA DIMENSION MISMATCH DURING MATRIX MULTIPLICATION //");
        }
        // Eigen automatically handles optimization vectors for this operation
        return QuantumOperator(dimension_, this->matrix_ * other.matrix_);
    }

    QuantumOperator QuantumOperator::operator*(const Complexd& scalar) const {
        return QuantumOperator(dimension_, this->matrix_ * scalar);
    }

    // ==============================================================================
    // NONCOMMUTATIVE TOPOLOGY METRICS
    // ==============================================================================

    // Enforces the core mathematical Lie Bracket: [A, B] = AB - BA
    QuantumOperator QuantumOperator::commutator(const QuantumOperator& A, const QuantumOperator& B) {
        if (A.dimension_ != B.dimension_) {
            throw std::invalid_argument("// COMMUTATOR ERROR: OPERATOR MATRIX DIMENSIONS MUST ALIGN //");
        }
        // Compute non-zero deviations to warp the pseudo-paradox space mesh
        return (A * B) - (B * A);
    }

    // Verifies if operators commute within a configurable numeric tolerance window
    bool QuantumOperator::commutes_with(const QuantumOperator& other, double epsilon) const {
        if (this->dimension_ != other.dimension_) {
            return false;
        }
        QuantumOperator diff = QuantumOperator::commutator(*this, other);
        // Track the Frobenius norm of the matrix deviation matrix
        return diff.get_raw_matrix().norm() <= epsilon;
    }

    // Ensures mathematical observables yield entirely real-valued eigenvalues
    bool QuantumOperator::is_hermitian(double epsilon) const {
        // A matrix is Hermitian if it equals its complex conjugate transpose (adjoint)
        return matrix_.isApprox(matrix_.adjoint(), epsilon);
    }

} // namespace PseudoParadox
EOF
