<h2 align="center"> PACKAGE PER L'INTERPOLAZIONE DELLA FUNZIONE ln(x + 1) + cos(x - 1) </h2>

<p align="center">
  <a href="">
  	<img src="https://img.shields.io/badge/Build-passing-blue.svg" height=25/>
  </a>
  <a href="https://github.com/riccardo-nigrelli/Interpolation/releases">
    <img src="https://img.shields.io/badge/Version-v0.1-e60026.svg" height=25/>
  </a>
</p>

Attraverso questo package do la possibilità all'utente di interpolare la funzione `ln(x + 1) + cos(x - 1)` attraverso il polinomio di Lagrange e il polinomio di Chebyshev con rappresentazione grafica di entrambi i metodi. Inoltre è possibile mettere a confronto i risultati delle due interpolazioni in un un unico grafico in modo da vedere quale tra i due metodi approssima meglio la funzione di partenza.

<h4> Pre-requisiti </h4>
Per l'utilizzo di questo tool è necessario aver installato [gnuplot].

<h4> Comandi di utilizzo </h4>
<table>
  <tr align="left">
    <th>Comando</th>
    <th>Descrizione</th>
  </tr>
  <tr>
    <td><code>make clean all</code></td>
    <td>Generare i file eseguibili</td>
  </tr>
  <tr>
    <td><code>./app/main</code></td>
    <td>Eseguire l'applicativo</td>
  </tr>
</table>

[gnuplot]: (http://www.gnuplot.info/)