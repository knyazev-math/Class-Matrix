# Class-Matrix
Class Matrix Realisation C++


Commands:
  1) m*\m — calculate multiplication of two matrices

  2) m+m — calculate sum of two matrices

  3) det — calculate matrix determinant

  4) m*\n — multiply matrix by a number

  5) m^t — transponse matrix

  6) gauss — gaussian elimination

  7) solve — solves system of linear equations

  8) jordan — finds the jordan form of the matrix (currently operating only for 2x2)




Inputs format:


1) Operation with two matrices


  <command: m*\m or m+m>
  
  <enter first matrix sides: strings, rows>
  
  <enter 1^st string of the matrix>
  
  <enter 2^nd string of the matrix>
  
  
  .
  
  .
  
  .
  
  <enter n^th string of the matrix>
  
  <enter second matrix sides: strings, rows>
  
  <enter 1^st string of the matrix>
  
  <enter 2^nd string of the matrix>
  
  .
  
  .
  
  .
  
  <enter n^th string of the matrix>
    
  Example:
  
  m+m
  
  2 2
  
  0 1
  
  1 0
  
  2 2
  
  1 0
  
  0 1
    
    
2) Operation with one matrix


  <command: det, m^t, gauss or jordan>
  
  <enter first matrix sides: strings, rows>
  
  <enter 1^st string of the matrix>
  
  <enter 2^nd string of the matrix>
  
  .
  
  .
  
  .
  
  <enter n^th string of the matrix>
  
  
  example:
  
  gauss
  
  2 3
  
  1 2 3
  
  4 5 6
  
  
3) Multiplying matrix by a number

  <command: m*\n>
  
  <enter first matrix sides: strings, rows>
  
  <enter 1^st string of the matrix>
  
  <enter 2^nd string of the matrix>
  
  .
  
  .
  
  .
  
  <enter n^th string of the matrix>
  
  <enter a number to multiply the matrix>
  
  
  example:
  
  m*\n
  
  2 3
  
  1 2 3
  
  4 5 6
  
  7
  
4) Solve a system of linear equations
  
  <command: solve>
    
  <enter the number of equations and the number of variables>
    
  <enter the coefficients of the 1^st equation>
    
  <enter the coefficients of the 2^nd equation>
    
  .
    
  .
    
  .
    
  <enter the coefficients of the n^th equation>
    
    
  example: having a system of linear equations x + 3y = 2, 2x - y = -10
  
  2 2
    
  1 3 2
    
  2 -1 3
    
    
 in general: having a system of linear equations a_{i, 1}x_1 + a_{i, 2}x_2 + ... + a_{i, m}x_m = b_i, i = 1... n
 
 n m
    
 a_{1, 1} a_{1, 2} ... a_{1, m} b_1
    
 a_{2, 1} a_{2, 2} ... a_{2, m} b_2
    
 .
    
 .
    
 .
    
 a_{n, 1} a_{n, 2} ... a_{n, m} b_n
 



