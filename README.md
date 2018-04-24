# Visualization of the mathematical pendulum

## Purpose of the programm

This program shows a visualization of the mathematical pendulum. It allows the adjustment of the parameters
- pendulum length
- amplitude
- gravity

for the underlying mathematical equation of motion as well as other settings for the visualization. It provides different pendulum types and different approximations for the equation of motion for choice. 

*Read this in [German](README.de.md) / Lesen Sie dies auf [Deutsch](README.de.md)*

## Table of Contents
  - [Screenshots](#screenshots)
  - [Controls](#controls)
  - [Mathematical Background](#mathematical-background)

## Screenshots

### Simple Pendulum
![Simple pendulum](https://i.imgur.com/gKjomPu.png)

### Simple Pendulums in both Approximations and with visible Values
![Simple pendulums in both approximations and with visible values](https://i.imgur.com/bBzF83o.png)

### Newton Pendulum
![Newton pendulum](https://i.imgur.com/pVR2XCE.png)

### Pendulums with invisible Wires
![Pendulums with invisible wires](https://i.imgur.com/ZgyH7l4.png)

## Controls 

*(Since the program is not yet translated into English, the german control notations are given in brackets)*

**Pendulum length (Pendellänge)** and **amplitude (Auslenkung)** can either be set by the corresponding controls or by dragging the pendulums ball with the mouse to the desired start position. (The ball can not be dragged out of the visualization area by the mouse, though it can leave the area after starting the pendulum by its movement.)

The **gravity (Schwerkraft)** can be chosen from predefined gravity values of some selected heavenly bodies from our solar system (including the earth). If "manually" is selected, an arbitrary value can be set.

The **radius (Radius)** of the pendulums ball and a **zoom factor (Zoom)** can also be chosen, but they don't have an effect on the pendulums motion.

Since the parameters pendulums length, amplitude and gravity have an impact on the pendulums motion, they can not be altered as long as the pendulum is moving. All other parameters can be changed at any time.

There are **2 pendulum types (Pendelart)** available: 
1. **Simple wire pendulum (einfach)** 
2. **Newton pendulum with 5 balls (5-Kugeln)**

Also there are **2 different approximations for the mathematical equation of motion (Pendelfunktion)** available:
1. **Small angle approximation (Kleinwinkelnäherung)**, based on a simplified differential equation. This approximation is rather inaccurate for angles > 20°
2. **Taylor approximation in 6st order (Taylornäherung)**, which is a clearly more accurate approximation
If the common wire pendulum is chosen, both approximations can be shown in two different pendulums at the same time to directly compare the difference in motion. To distinguish them, they can be shown in different colors. 

The pendulum can be started and stopped by the **start/stop button**. Alternatively it can be started and stopped by the mouse, if the option "instant start by mouse" is activated.

The following **options (Optionen)** are available:
- **pendulum wire visible (Pendelfaden sichtbar)**: if deactivated, the pendulum wire will be invisible
- **show scale (Skala anzeigen)**: If activated, a scale will be shown at the right side of the visualization area
- **show values (Werte anzeigen)**: If activated, there will be shown the run-time, as well as the values of current coordinates, angle, period and number of zero passes for both approximations
- **instant start by mouse (Maus-Direktstart)**: if activated, the pendulum starts instantly after it got dragged by the mouse. It will stop by just clicking on the visualization area. (The start/stop button will keep its functionality)

## Mathematical Background

The differential equation, which describes the pendulums motion is given by

![Equation (1)](https://i.imgur.com/MCq7KrC.png)  
In this equation appears the amplitude angle φ at the time t as well as its second time derivative φ̈ , which describes the angular acceleration. Now to simulate the pendulums motion, the differential equation has to be solved. To achieve that, two approaches were pursued.  
The first one is to simplify the matter by presuming, that for small angles applies sin(φ) ≈ φ. The resulting simplified differential equation 

![Equation (2)](https://i.imgur.com/4UailUM.png)  
is solvable. For that a time-dependant function has to be found, which results in its second derivative, if multiplied by the factor −g/l. As a solution the equation 

![Equation (3)](https://i.imgur.com/pen3hT3.png)  
is found with the periodic time

![Equation (4)](https://i.imgur.com/jPOPgf3.png)  
(Further Information about the mathematical derivation can be found at [https://lp.uni-goettingen.de/get/text/7371](https://lp.uni-goettingen.de/get/text/7371).)  
This solution is applied in the program as pendulum function with the notation **Small angle approximation (Kleinwinkelnäherung)**. However it is rather unprecise for angles > 20°.

The second approach provides a more accurate solution. It comes from the original equation of motion without simplifications. The resulting solution for the periodic time T is

![Equation (5)](https://i.imgur.com/uZhqlaT.png)  
This integral is not elementary solvable, but it can be approximated by the Taylor approximation. Performed to the 6st degree it leads to the approximated periodic time of 

![Equation (6)](https://i.imgur.com/yuTZzyl.png)  
This solution is applied in the program as pendulum function with the notation **Taylor approximation (Taylornäherung)**.
