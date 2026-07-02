import pandas as pd
import matplotlib.pyplot as plt

# Load the C output
df = pd.read_csv("legendre_errors.csv")

# ==========================================
# CLAMP ERRORS TO 1e-17
# ==========================================
# Apply a lower bound of 1e-17 to all error columns
error_cols = ['err_fwd_rel', 'err_bwd_rel', 'err_fwd_abs', 'err_bwd_abs']
for col in error_cols:
    df[col] = df[col].clip(lower=1e-17)

x_values = df['x'].unique()

# ==========================================
# PLOT 1: RELATIVE ERROR
# ==========================================
fig_rel, axes_rel = plt.subplots(2, 2, figsize=(12, 10))
axes_rel = axes_rel.flatten()

for i, x in enumerate(x_values):
    subset = df[df['x'] == x]
    
    ax = axes_rel[i]
    ax.plot(subset['l'], subset['err_fwd_rel'], 'r.-', label='Forward Recurrence')
    ax.plot(subset['l'], subset['err_bwd_rel'], 'b.-', label='Backward (Miller)')
    
    ax.set_yscale('log')
    ax.set_title(f'Relative Error for x = {x}')
    ax.set_xlabel('Degree (ℓ)')
    ax.set_ylabel('Relative Error')
    ax.set_ylim(1e-17, 1e2)
    ax.grid(True, which="both", ls="--", alpha=0.5)
    ax.legend()

fig_rel.tight_layout()
fig_rel.savefig("legendre_relative_errors_plot.png") # Save before show!

# ==========================================
# PLOT 2: ABSOLUTE ERROR
# ==========================================
fig_abs, axes_abs = plt.subplots(2, 2, figsize=(12, 10))
axes_abs = axes_abs.flatten()

for i, x in enumerate(x_values):
    subset = df[df['x'] == x]
    
    ax = axes_abs[i]
    ax.plot(subset['l'], subset['err_fwd_abs'], 'r.-', label='Forward Recurrence')
    ax.plot(subset['l'], subset['err_bwd_abs'], 'b.-', label='Backward (Miller)')
    
    # Optional: If you want the absolute error to also be log-scale so the 1e-17 floor is visible
    # ax.set_yscale('log') 
    
    ax.set_title(f'Absolute Error for x = {x}')
    ax.set_xlabel('Degree (ℓ)')
    ax.set_ylabel('Absolute Error')
    ax.set_ylim(0, 10) # Note: If you switch to log scale, update these limits!
    ax.grid(True, which="both", ls="--", alpha=0.5)
    ax.legend()

fig_abs.tight_layout()
fig_abs.savefig("legendre_absolute_errors_plot.png") # Save before show!

# Show both figures at t