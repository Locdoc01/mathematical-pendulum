# Visualisierung des Mathematischen Pendels

## Zweck des Programms

Das Programm zeigt eine Visualisierung des Mathematischen Pendels. Es erlaubt die Einstellung der Parameter für die Bewegungsgleichung
- Pendellänge
- Auslenkung
- Schwerkraft

sowie weiterer Einstellungsmöglichkeiten für die Visualisierung. Es stellt verschiedene Pendelarten sowie Approximationen der Bewegungsgleichung zur Auswahl.

*Lesen Sie dies auf [Englisch](README.md) / Read this in [English](README.md)*

## Inhalt
  - [Screenshots](#screenshots)
  - [Bedienung](#bedienung)
  - [Mathematischer Hintergrund](#mathematischer-hintergrund)

## Screenshots

### Einfaches Pendel
![Einfaches Pendel](https://i.imgur.com/gKjomPu.png)

### Einfache Pendel in beiden Approximationen und mit angezeigten Werten
![Einfache Pendel in beiden Approximationen und mit angezeigten Werten](https://i.imgur.com/bBzF83o.png)

### Newton-Pendel
![Newton-Pendel](https://i.imgur.com/pVR2XCE.png)

### Pendel mit unsichtbaren Fäden
![Pendel mit unsichtbaren Fäden](https://i.imgur.com/ZgyH7l4.png)

## Bedienung

**Pendellänge** und **Amplitude** können entweder über die entsprechenden Bedienelemente eingestellt werden, oder durch Ziehen der Pendelkugel mit der Maus auf die gewünschte Startposition. (Die Kugel kann mit der Maus nicht aus der Visualisierungsfläche herausgezogen werden, allerdings kann sie die Fläche nach dem Start durch die Pendelbewegung zeitweise verlassen.)

Die **Schwerkraft** kann aus vordefinierten Schwerkraftwerten ausgesuchter Himmelskörper unseres Sonnensystems (inklusive der Erde) ausgewählt werden. Falls "Manuell" ausgewählt wird, kann ein beliebiger Wert eingestellt werden.

Der **Radius** der Pendelkugel und der **Zoom-Faktor** könnnen ebenfalls ausgewählt werden, aber sie haben keinen Effekt auf die Pendelbewegung.

Da die Parameter Pendellänge, Auslenkung und Schwerkraft die Pendelbewegung beeinflussen, können sie nicht geändert werden, solange das Pendel sich bewegt. Die anderern Parameter können jederzeit geändert werden. 

Es sind **2 Pendelarten** verfügbar:
1. **Einfaches Fadenpendel**
2. **Newton-Pendel mit 5 Kugeln**

Außerdem sind **2 verschiedene Approximationen für die mathematische Bewegungsgleichung** verfügbar:
1. **Kleinwinkelnäherung**, basierend auf einer vereinfachten Differentialgleichung. Diese Approximation ist eher ungenau für Winkel > 20°.
2. **Taylornäherung 6. Ordnung**. Diese Approximation ist deutlich genauer.
Falls das normale Fadenpendel ausgewählt ist, können beide Approximationen in zwei verschiedenen Pendeln gleichzeitig angezeigt werden, um den Unterschied in der Bewegung direkt zu vergleichen. Zur Unterscheidung sind verschiedene Farben wählbar.

Das Pendel kann durch den **Start/Stopp-Button** gestartet und gestoppt werden. Alternativ kann es mithilfe der Mouse gestarted und gestoppt werden, wenn die Option "Maus-Direktstart" aktiviert ist.

Die folgenden **Optionen** sind verfügbar:
- **Pendelfaden sichtbar**: Falls deaktiviert, ist der Pendelfaden unsichtbar
- **Skala anzeigen**: Falls aktiviert, wird eine Skala auf der rechten Seite des Visualisierungsbereichs angezeigt
- **Werte anzeigen**: Falls aktiviert, wird die Laufzeit sowie die Werte für aktuelle Koordinaten, Winkel, Periode und Anzahl der Nulldurchgänge beider Approximationen angezeigt
- **Maus-Direktstart**: Falls aktiviert, startet das Pendel direkt, wenn es mit der Maus gezogen wurde. Durch Klicken auf den Visualisierungsbereich wird es wieder gestoppt (Der Start/Stopp-Button behält seine Funktionalität)

## Mathematischer Hintergrund

Die Differentialgleichung, die die Bewegung des Pendels beschreibt, ist gegeben durch

![Gleichung (1)](https://i.imgur.com/MCq7KrC.png)  
Hier taucht der Auslenkungswinkel φ zum Zeitpunkt t sowie seine zweite Zeitableitung φ̈ auf, welche die Winkelbeschleunigung beschreibt. Um die Bewegung des Pendels nun zu simulieren, muss die Differentialgleichung gelöst werden. Hierfür wurden zwei Ansätze verfolgt.
Beim ersten Ansatz wird zur Vereinfachung angenommen, dass für kleine Winkel sin(φ) ≈ φ ist. Die daraus resultierende vereinfachte Differentialgleichung

![Gleichung (2)](https://i.imgur.com/4UailUM.png)  
ist lösbar. Dazu wird eine von der Zeit abhängige Funktion gesucht, die mit dem Vorfaktor −g/l multipliziert ihre zweite Ableitung ergibt. Als Lösung wird die Funktion

![Gleichung (3)](https://i.imgur.com/pen3hT3.png)  
gefunden mit der Periodendauer

![Gleichung (4)](https://i.imgur.com/jPOPgf3.png)  
(Weitere Informationen zur mathematischen Herleitung sind unter [https://lp.uni-goettingen.de/get/text/7371](https://lp.uni-goettingen.de/get/text/7371) zu finden.)  
Diese Lösung wird im Programm als Pendelfunktion mit der Bezeichnung **Kleinwinkelnäherung** verwendet. Sie ist jedoch für Winkel > 20° eher ungenau.

Der zweite Lösungsansatz bietet eine exaktere Lösung. Hierbei wird von der originalen Bewegungsgleichung ohne Vereinfachung ausgegangen. Für die Periodendauer T erhält man dann die Lösung

![Gleichung (5)](https://i.imgur.com/uZhqlaT.png)  
Dieses Integral ist nicht elementar lösbar, kann aber durch eine Taylorapproximation angenähert werden. Führt man diese bis zum Grad 6 durch, kommt man auf eine angenäherte Periodendauer von

![Gleichung (6)](https://i.imgur.com/yuTZzyl.png)  
Diese Lösung wird im Programm als Pendelfunktion mit der Bezeichnung **Taylornäherung** verwendet.

