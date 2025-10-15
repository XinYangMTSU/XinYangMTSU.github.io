"""
Simple Linear SVM Demo
3 functions: make_data, plot_svm, compare_C
"""

import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC

np.random.seed(42)

# ============================================
# FUNCTION 1: Make Data (Easy!)
# ============================================
def make_data():
    """Create simple 2D data - two clusters"""
    # Blue class (bottom-left)
    X1 = np.random.randn(50, 2) + [-2, -2]
    
    # Red class (top-right)
    X2 = np.random.randn(50, 2) + [2, 2]
    
    # Combine
    X = np.vstack([X1, X2])
    y = np.array([0]*50 + [1]*50) # Create Labels
    
    return X, y

# ============================================
# FUNCTION 2: Plot SVM 
# ============================================
def plot_svm(X, y, C, ax):
    """Train SVM and plot everything"""
    
    # Train SVM
    svm = SVC(kernel='linear', C=C)
    svm.fit(X, y)
    
    # Get line parameters: w·x + b = 0
    w = svm.coef_[0]
    b = svm.intercept_[0]
    
    # Create x points
    x_points = np.linspace(-5, 5, 100)
    
    # Calculate y for three lines
    y_boundary = -(w[0] * x_points + b) / w[1]      # Decision boundary
    y_margin_up = -(w[0] * x_points + b - 1) / w[1]  # Upper margin
    y_margin_down = -(w[0] * x_points + b + 1) / w[1] # Lower margin

    '''
    w₁·x₁ + w₂·x₂ + b = 0
    
    Solve for x₂ (which is y in our plot):
    w₂·x₂ = -w₁·x₁ - b
    x₂ = -(w₁·x₁ + b) / w₂
    
    In our code:
    x₁ = x_points  (horizontal axis)
    x₂ = y values  (vertical axis)
    w₁ = w[0]
    w₂ = w[1]
    '''
    
    # Plot the lines
    ax.plot(x_points, y_boundary, 'k-', linewidth=3, label='Boundary')
    ax.plot(x_points, y_margin_up, 'b--', linewidth=2, label='Margin')
    ax.plot(x_points, y_margin_down, 'r--', linewidth=2)
    
    # Plot data points
    ax.scatter(X[y==0, 0], X[y==0, 1], c='blue', s=50, label='Class 0')
    ax.scatter(X[y==1, 0], X[y==1, 1], c='red', s=50, label='Class 1')
    
    # Plot support vectors (bigger circles)
    ax.scatter(svm.support_vectors_[:, 0], 
              svm.support_vectors_[:, 1],
              s=200, facecolors='none', edgecolors='green', 
              linewidths=3, label='Support Vectors')
    
    # Calculate stats
    margin_width = 2 / np.linalg.norm(w)
    n_sv = len(svm.support_vectors_)
    acc = svm.score(X, y)
    
    # Add title with stats
    ax.set_title(f'C={C} | Margin={margin_width:.2f} | SVs={n_sv} | Acc={acc:.2%}',
                fontsize=12, fontweight='bold')
    ax.legend()
    ax.grid(True, alpha=0.3)
    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)

# ============================================
# FUNCTION 3: Compare Different C Values
# ============================================
def compare_C():
    """Compare 3 different C values"""
    
    # Make data once
    X, y = make_data()
    
    # Three C values to compare
    C_values = [0.01, 1, 100]
    
    # Create 3 subplots
    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    #fig   # The entire figure (like a canvas)
    #axes  # Array of 3 subplot objects
    #axes[0]  # Left subplot
    #axes[1]  # Middle subplot  
    #axes[2]  # Right subplot
    
    # Plot each one
    for i, C in enumerate(C_values):
        plot_svm(X, y, C, axes[i])
    
    plt.suptitle('Linear SVM: Effect of C Parameter', fontsize=16, fontweight='bold')
    plt.tight_layout()
    plt.savefig('simple_svm_demo.png', dpi=150, bbox_inches='tight')
    print("Saved: simple_svm_demo.png")
    plt.show()

# ============================================
# BONUS: Interactive Single Plot
# ============================================
def single_plot(C=1):
    """Plot just one SVM - good for testing"""
    X, y = make_data()
    
    fig, ax = plt.subplots(figsize=(8, 6))
    plot_svm(X, y, C, ax)
    
    plt.tight_layout()
    plt.show()

# ============================================
# RUN IT!
# ============================================
if __name__ == "__main__":
    print("Running Simple SVM Demo...")
    compare_C()
    print("\nDone! Check 'simple_svm_demo.png'")
    
    #Just try one C value
    single_plot(C=0.1)

# 0.01 = Very small C (soft margin)
# 1 = Medium C (balanced)
# 100 = Very large C (hard margin)
