Bruteforce: `Goldstein-Price function - Time: 0.062 Point: 3.00949 X -> -0.001711 Y -> -1.00494` <br>
Anneal: `Goldstein-Price function - Time: 0.035 Point: 30.0762 X -> -0.60261 Y -> -0.405634`<br>
Hill Climbing: `Goldstein-Price function - Time: 0.015 Point: 30.0342 X -> -0.600514 Y -> -0.394363`<br>
---------------------------------------------
Bruteforce: `Himmelblau's function - Time: 0.051 Point: 0.000909331 X -> 3.58372 Y -> -1.8557`<br>
Anneal:`Himmelblau's function - Time: 0.026 Point: 0.00124877 X -> 3.00571 Y -> 2.00034`<br>
Hill Climbing:`Himmelblau's function - Time: 0.012 Point: 0.000330234 X -> -2.80202 Y -> 3.13194`<br>
---------------------------------------------
Bruteforce: `Booth function - Time: 0.047 Point: 0.00333573 X -> 1.00877 Y -> 2.9677`<br>
Anneal:`Booth function - Time: 0.024 Point: 2.20913e-05 X -> 0.997709 Y -> 3.00342`<br>
Hill Climbing:`Booth function - Time: 0.01 Point: 7.70825e-06 X -> 0.999788 Y -> 2.99893`<br>
<br>
Wygląda na to że najdłużej działa algoytm **Bruteforce**. Niemal dla każdej funkci testowej wykazuje najwyższy czas
jednakże też pokazuje najlepszy wynik dla każdej funkcji.<br>
**Hill climbing** pokazuje poprawnie minimum dla minimum lokalnych (jeśli mamy farta to globanych) lub przeznaczony
jest dla funkcji gdzie jest tylko minimum globalne. <br>
**Anneal** nie działa