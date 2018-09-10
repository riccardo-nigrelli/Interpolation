<h2 align="center"> PACKAGE FOR INTERPOLATION OF ln(x + 1) + cos(x - 1) FUNCTION</h2>

<p align="center">
  <a href="">
  	<img src="https://img.shields.io/badge/Build-passing-blue.svg" height=25/>
  </a>
  <a href="https://github.com/riccardo-nigrelli/Interpolation/releases">
    <img src="https://img.shields.io/badge/Version-v0.1-e60026.svg" height=25/>
  </a>
</p>

Through this package I give the user the possibility to interpolate the function `ln (x + 1) + cos (x - 1)` through the Lagrange polynomial and the Chebyshev polynomial with graphic representation of both methods. Furthermore, it is possible to compare the results of the two interpolations in a single graph in order to see which of the two methods best approximates the starting function.

<h4> Prerequisites </h4>
To use this tool you need to have <a href="http://www.gnuplot.info/"> gnuplot </a> and git installed.

<h4> Usage commands </h4>
<table>
  <tr align="left">
    <th>Command</th>
    <th>Description</th>
  </tr>
  <tr>
    <td><code>make clean all</code></td>
    <td>Generate executable files</td>
  </tr>
  <tr>
    <td><code>./app/main</code></td>
    <td>Run the application</td>
  </tr>
</table>
