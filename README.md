<h2 align="center"> PACKAGE PER L'INTERPOLAZIONE DELLA FUNZIONE ln(x + 1) + cos(x - 1) </h2>

<p align="center">
  <img src="https://camo.githubusercontent.com/a47a8f66fe9b2e73f4e364ac938060c825dc66fb/68747470733a2f2f73656d6170686f72656170702e636f6d2f6170692f76312f70726f6a656374732f64346363613530362d393962652d343464322d623139652d3137366633366563386366312f3132383530352f62616467652e737667" alt="Build Status" data-canonical-src="https://semaphoreapp.com/api/v1/projects/d4cca506-99be-44d2-b19e-176f36ec8cf1/128505/badge.svg" style="max-width:100%;">
</p>

Attraverso questo package do la possibilità all'utente di interpolare la funzione `ln(x + 1) + cos(x - 1)` attraverso il polinomio di Lagrange e il polinomio di Chebyshev con rappresentazione grafica di entrambi i metodi. Inoltre è possibile mettere a confronto i risultati delle due interpolazioni in un un unico grafico in modo da vedere quale tra i due metodi approssima meglio la funzione di partenza.

<h4> Pre-requisiti </h4>
Per l'utilizzo di questo tool è necessario aver installato <code>gnuplot</code>

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