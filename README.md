# SimpleMagnetSim
This is a magnet simulator that I made for a physics presentation in school. I learned how to use OpenGL, vectors, and how to apply the mathematics I learned in school to create this project. I'm really proud with how it turned out. 

<p align="center"><img src="https://github.com/user-attachments/assets/e32ee763-7ab8-4753-a522-9b94fac10e70" height=400 width=400></p>

## Learning OpenGL 
<p>I needed to learn OpenGL to make the simulator. To do this, I used youtube videos and made my own projects to practice before moving on with this project.</p> 
<p align="center">
<img src="https://github.com/user-attachments/assets/6265e1d7-d884-44bf-8130-af4d44e27d5e" height="250" width="250">
<img src="https://github.com/user-attachments/assets/1a9c8c86-2fbe-474c-9e7f-7d319cf82a95" height="250" width="250">
<img src="https://github.com/user-attachments/assets/d7e7d16f-8de0-465a-ae0e-489d2fa316e4" height="250" width="250">
</p>

## Learning the maths
I tried learning the mathematics behind drawing a magnetic field and implementing them into the draw loop, but it proved to be very complicated and complex. Something simpler was need. So, I decided to replace it with circles that act as the magnetic field. 

<p align="center"><em>The magnetic field drawn as circles</em></p>
<p align="center"><img src="https://github.com/user-attachments/assets/0c9597ad-41e5-4c78-8e8a-52f8c93c8339" height="250" width="250"></p>

## Applying the maths
First, I needed to calculate the **vector** between the center of the magnetic object and the magnet. Then, check whether the object **intersected** with the magnetic field. If true, then update the position of the center of the circle towards the closest pole of the magnet. 

<p align="center"><em>The magnetic object inside the magnetic field</em></p>
<p align="center"><img src="https://github.com/user-attachments/assets/a83c8956-b53d-4432-9ee1-f080aa3b5b86" height="250" width="250"></p>

## End Product
The simulation shows a grey, magnetic circle and a bar magnet with a magnetic field surrounding it. If the circle is within or intersecting the magnetic field, it moves towards one of closest pole--North or South. The circles position is reset after it touches the magnet

![20251211_063111-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/2becbbf9-62e9-40d4-8842-2791e9cef343)





