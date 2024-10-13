# Lightlink
<p align="center">
  <img src="_img/main.jpg" width="50%" alt="Picture of a light link device" style="border-radius: 5px;"/>
  <br />
  <i>The light link devices. </i>
</p>
<br />

<div style="text-align: justify">
Light Link is a device that allows you to create pixel art on your smartphone and display it on an LED matrix.
Using an easy-to-use website, you can draw, edit, and customize your designs. Once your masterpiece is ready,
send it wirelessly to Light Link and see your art in vibrant colors. Perfect for decorating your space, creating
unique displays, or sharing with friends, Light Link combines creativity and technology.
</div>
<br />


# The project
<div style="text-align: justify">
This project is an engineering school assignment completed during the second semester of 2024.
The main goal of this project was to connect people separated by distance, allowing them to draw small things on the device's screen using their phone.
</div>
<br />


# How the device work
<div style="text-align: justify">
The device is designed to work in pair with your phone. It connects to the internet to fetch drawings using your mobile data (shared hotspot). Once the device is connected to the internet, it will display the last drawing sent by your partner, and after 30 seconds, it goes to sleep to save some battery.
<br />
<br />
To send a drawing, all you need is your phone and an internet connection. Simply scan the QR code displayed on the device's backscreen and start drawing using the web app!
</div>

## Electronics
<p align="center">
  <img src="_img/schematic.png" width="100%" alt="A picture of the electronic schematic" style="border-radius: 5px;"/>
  <br />
  <i>The schematic for the whole project. </i>
</p>
<div style="text-align: justify">
The device is using an ESP32 as microcontroller and a 8x8 LED matrix for the main display. At the back of the device, there 
is also an second screen to display some useful information like the battery level or the wifi strength. Light link is also 
equiped with a vibration motor to ensure that you don't miss any new drawings and also a vibration switch sensor
to wake the device up by tapping or shaking it. 
<br />
<br />
Every component is holded and connected together using a custom made PCB. Thanks to PCBWay that sponsored our project, we got 
those custom PCB for free! But before ordering them I made some prototype PCB board using a CNC machine. 
</div>
<br />

<p align="center">
  <img src="_img/prototype_pcb.jpg" width="47%" alt="A picture of the prototype PCB" style="border-radius: 5px;"/>
  <img src="_img/production_pcb.jpg" width="47%" alt="A picture of the production PCB" style="border-radius: 5px;"/>
  <br />
  <i>On the left, the prototype board made with my CNC and on the right the production PCB. </i>
</p>


## Web server
<div style="text-align: justify">
For the device, to be able to display drawings, we needed to create an API were you can fetch and send drawing to. This API is written in python and
is capable of receive new drawings from an HTTP POST request and send drawings with a simple HTTP call that will return the latest drawing in JSON format. 
The device call for that JSON data, decode it and then displays it to the main screen!

To be able to fetch drawings everywhere on earth, the API is hosted on a machine running ubuntu-server an opened to the world-wide-web. 

<p align="center">
  <img src="_img/ui.PNG" width="47%" alt="A picture of the web app" style="border-radius: 5px;"/>
  <img src="_img/ui2.PNG" width="47%" alt="A picture of the web app" style="border-radius: 5px;"/>
  <br />
  <i>The web app used to send a drawing. </i>
</p>
</div>

# Manufacturing
<div style="text-align: justify">
The device is composed of two independant piece that need to be manufactured. 
</div>

## The plastic shell 
<div style="text-align: justify">
The plastic shell is 3D printed in PLA and is composed of 3 separate pieces, the case the light diffuser and the back cover. The case and back cover are holded together
using some small neodymium magnets to be able to open the device very quickly and easily and the diffuser is press fitted inside the case. 
<br />
</div>
<p align="center">
  <img src="_img/case_diffuser_back_cover.png" width="100%" alt="A picture of the case" style="border-radius: 5px;"/>
  <img src="_img/shell_case.png" width="100%" alt="A picture of the case" style="border-radius: 5px;"/>
  <br />
  <i>The plastic case disassembled. </i>
</p>

## The board
<div style="text-align: justify">
As I said before, PCBs were sent by PCBWay, but before that we needed to engrave some PCBs using my CNC machine to see 
if everything works as intended before ordering production PCBs. The PCB, after the soldering of every component, is press
fitted inside the case. 
</div>
<br />

<p align="center">
  <img src="_img/cnc.jpg" width="47%" alt="A picture of the prototype PCB" style="border-radius: 5px;"/>
  <br />
  <i>The process of engraving prototypes PCBs. </i>
</p>

## Result 
<div style="text-align: justify">
And here is the result!

<br />
</div>
<p align="center">
  <img src="_img/devices.jpg" width="75%" alt="A picture of two light link devices" style="border-radius: 5px;"/>
  <img src="_img/devices_.jpg" width="75%" alt="A picture of two light link devices" style="border-radius: 5px;"/>
  <br />
  <i>The device completed. </i>
</p>




# Conclusion
<div style="text-align: justify">
Out of all electronics project that I made over the years, this one is the one that I'm the most proud of. I mastered lots of 
need skills like designing a PCB, using a CNC machine, engrave my own circuit board, creating a small API, make HTTP calls using
a microcontroller and much more. In addition to this, it is super rewarding to see the finished product working correctly ; And since this is a school project. And it is even more rewarding to get a nice grade out of it :).
</div>

# Licence
- romainflcht