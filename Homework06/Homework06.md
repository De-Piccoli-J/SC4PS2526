# Homework 6

This folder contains a C programs that compute the vector operation:

$$
\vec{d} = a \vec{x} + \vec{y}
$$

The programs allow the user to specify from a `config.txt` file:

- The size $N$ of the vectors $\vec{x}$ and $\vec{y}$  
- The scalar value $ a $  
- The value assigned to all elements of $\vec{x}$ and $\vec{y}$ 
- The chuck size 

The operation is done in chucks and it is validated against the algorithm in `Homework02`

The resulting vector and the sum of the various chucks is then printend in a HDF5 file `results.h5`
