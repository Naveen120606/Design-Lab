# Autonomous Vacuum Cleaner

This repository contains the design and implementation details for an Autonomous Vacuum Cleaner, developed as a prototype for the EE396 Design Lab. 

**Authors:** Chandan Jyoti Das & Naveen Kumawat (ECE Department)  
**Supervisor:** Prof. Tanmay Dutta

---

## Project Overview
The primary objective of this project is to conceptualize and build a self-navigating robotic system capable of autonomous floor cleaning without human intervention. Rather than relying on manual operation, the device uses real-time environmental feedback to make navigational decisions while actively sweeping and capturing debris.

## Hardware & Mechanical Design
* **Chassis:** A circular acrylic open-chassis design was selected to enhance rotational maneuverability and prevent the robot from getting stuck in corners. 
* **Locomotion:** The robot utilizes a differential drive system powered by two rear robotic wheels and stabilized by a single front caster wheel, allowing for a zero-degree turning radius. Rubber bands were added over the wheel circumferences to prevent skidding.
* **Mechanical Stabilization:** To counteract wheel wobble, custom 3D-printed coupling shafts were created to securely connect the wheels to the DC motors. The mounts were rigidly locked in place using M-Seal epoxy putty.
* **Power Distribution:** The system is powered by a central 12V battery supply. To prevent logic-level voltage drops and motor stalling, a dedicated buck converter delivers a stable, high-current operating voltage directly to the L293D motor driver.
* **Controller:** A central Arduino controller handles the system's logic and spatial processing.

## Navigation & Sensors
* The robot relies on an array of three ultrasonic sensors securely mounted along the front perimeter. 
* These sensors provide a wide detection angle for spatial awareness, allowing the Arduino to halt the drive motors and prevent collisions when physical impediments are detected.

## Cleaning Module
* **Sweeping Mechanism:** Two front rotary brushes are driven by heavy-duty, high-torque DC motors to ensure consistent rotation. The bristle length was manually trimmed so they glide just above the floor, reducing drag and preventing the motors from stalling while guiding loose debris toward the center.
* **Suction System:** A central circular suction pipe is positioned close to the floor to maximize static pull. The primary vacuum module effectively captures lightweight particulate matter, such as standard floor dust and chalk powder, and routes it directly into an attached dust bag. 

## Future Prospects
Several improvements are planned for future iterations of this prototype:
* **Power Upgrades:** Upgrading the 12V power architecture to support a higher-wattage vacuum motor for handling heavier or denser debris.
* **Advanced Navigation:** Integrating room mapping capabilities or floor-type detection to optimize cleaning routes.
* **Enclosure Design:** Developing a custom, lightweight 3D-printed top cover to enclose and protect the circuitry (Arduino, motor drivers, buck converter) from dust.
* **Self-Charging:** Adding an automatic self-charging dock to enable continuous operation without human intervention.

## References
* Autodesk Instructables: [Procedure for making a Autonomous DIY Vacuum Robot](https://www.instructables.com/Build-Your-Own-Vacuum-Robot/)
* Zoo.dev: [Text-to-CAD software used for printing the CAD design on acrylic sheet](https://text-to-cad.zoo.dev/)
