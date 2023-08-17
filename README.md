<html>

<head>
<meta http-equiv="Content-Language" content="es">
<meta name="GENERATOR" content="Microsoft FrontPage 4.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
</head>

<font size="4"><b><i>Melanie-I&nbsp;</i></b></font>
      <p>By Alejandro Alonso Puig<br>
      March 2004<br>
 
<hr>
<i>Melanie-I was developed by Alejandro Alonso on March 2004</i><br />
<br />
<div style="text-align: justify;">
Melanie is an hexapod robot of 3 degrees of freedom by leg, that by the novel design of legs it has, can transport several kilograms on its body without electrical power overload.</div>
<br />
<p align="center"><img border="0" src="http://2.bp.blogspot.com/-eZRr-Ntbdxw/UuOVIK8IDpI/AAAAAAAAJYs/BvNT9_0rnFI/s1600/melanie.jpg" width="600" ></p>
<div style="text-align: justify;">
The version I that is in this technical report refers the simplest version of the implementation of the robot, in which the robot is connected to an external PC by serial port (RS232C) for its control by a Visual C++ application. See Video with <a href="https://youtu.be/Z-d1kQu70TE">Melanie lifting and walking with 1Kg payload</a></div>
<br />
There is a version II with superior capacities. Complete information could be obtained here: <b><u><a href="http://automacomp.blogspot.com.es/2004/04/melanie-ii-robust-hexapod-robot-of-3.html">Melanie-II</a></u></b><br />
<br />
Some basic characteristics that define Melanie v1.0 are the following:<br />
</b><br />
<ul>
<li>Size (cm): 33 x 31 x 12&nbsp;</li>
<li>Weight: 2,2Kg</li>
<li>Six legs</li>
<li>Three degrees of freedom per leg</li>
<li>Driven by RC servos (Twelve of 3kgcm and six of 5kgcm)</li>
<li>"smoothed" Control of servos by using a driver with speed management.</li>
<li>Communication with master PC by serial port RS232C</li>
<li>Distance measurement infrared sensor located at the front and able to be oriented</li>
<li>Structure of PVC and Aluminum</li>
<li>Battery of 6v NiMH 3300mAh for the servos</li>
<li>Battery of 9v NiMH for the control electronics</li>
<li>Control program in PC developed in Visual C++ 6.0</li>
</b><br />
</ul>
In this work there will be mention to all the mechanical,electronic and programming aspects, as well as conclusions of the experience.
<br>
<br>
More information: <br>
<ul>
  <li><p align="justify"><a href="Documentation\melanie-I_doc_en.pdf">Technical documentation</a></li>
  <li><p align="justify"><a href="Melanie-I_Program">Program</a></li>
  <li><p align="justify"><a href="Media">Pictures</a></li>
  <li><p align="justify"><a href="https://github.com/aalonsopuig/Melanie-II_Hexapod_Robot.git">Repository of Melanie-II</a></li>
  <li><p align="justify"><a href="https://github.com/aalonsopuig/Melanie-III_Hexapod_Robot.git">Repository of Melanie-III</a></li>
</ul>

</body>

</html>
