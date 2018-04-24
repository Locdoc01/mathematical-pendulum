# Visualization of the mathematical pendulum

## Purpose of the programm

This program shows a visualization of the mathematical pendulum. It allows the adjustment of the parameters
- pendulum length
- amplitude
- gravity

for the underlying mathematical equation of motion as well as other settings for the visualization. It provides different pendulum types and different approximations for the equation of motion for choice. 

*Read this in [German](README.de.md) / Lesen Sie dies auf [Deutsch](README.de.md)*

## Screenshots

### Simple pendulum
![Simple pendulum](https://i.imgur.com/gKjomPu.png)

### Simple pendulums in both approximations and with visible values
![Simple pendulums in both approximations and with visible values](https://i.imgur.com/bBzF83o.png)

### Newton pendulum
![Newton pendulum](https://i.imgur.com/pVR2XCE.png)

### Pendulums with invisible wires
![Pendulums with invisible wires](https://i.imgur.com/ZgyH7l4.png)

## Controls 

**Pendulum length** and **amplitude** can either be set by the corresponding controls or by dragging the pendulums ball with the mouse to the desired start position. (The ball can not be dragged out of the visualization area by the mouse, though it can leave the area after starting the pendulum by its movement.)

The **gravity** can be chosen from predefined gravity values of some selected heavenly bodies from our solar system (including the earth). If "manually" is selected, an arbitrary value can be set.

The **radius** of the pendulums ball and a **zoom factor** can also be chosen, but they don't have an effect on the pendulums motion.

Since the parameters pendulums length, amplitude and gravity have an impact on the pendulums motion, they can not be altered as long as the pendulum is moving. All other parameters can be changed at any time.

There are **2 pendulum types** available: 
1. **Simple wire pendulum** 
2. **Newton pendulum with 5 balls**

Also there are **2 different approximations for the mathematical equation of motion** available:
1. **Small angle approximation**, based on a simplified differential equation. This approximation is rather inaccurate for angles > 20°
2. **Taylor approximation in 6st order**, which is a clearly more accurate approximation
If the common wire pendulum is chosen, both approximations can be shown in two different pendulums at the same time to directly compare the difference in motion. To distinguish them, they can be shown in different colors. 

The pendulum can be started and stopped by the **start/stop button**. Alternatively it can be started and stopped by the mouse, if the option "instant start by mouse" is activated.

The following **options** are available:
- **pendulum wire visible**: if deactivated, the pendulum wire will be invisible
- **show scale**: If activated, a scale will be shown at the right side of the visualization area
- **show values**: If activated, there will be shown the run-time, as well as the values of current coordinates, angle, period and number of zero passes for both approximations
- **instant start by mouse**: if activated, the pendulum starts instantly after it got dragged by the mouse. It will stop by just clicking on the visualization area. (The start/stop button will keep its functionality)

## Mathematical background
