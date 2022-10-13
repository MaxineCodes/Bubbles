![image](https://github.com/MaxineCodes/Bubbles/blob/master/Bubbles/img/banner.png)

# Bubbles Raytracing Renderer
 
The Bubbles raytracing rendering engine is a GUI offline raytracing engine project which only renders `Bubbles` (spheres) using C++. <br/>
Qt is used for the GUI. 2D graphics & icons are made with Adobe Illustrator.

---

The Bubbles app will be a relatively simple 3D DCC program, where you can place spheres around the scene, assign materials, and render a final image. <br/>
My focus on this project is to get it to work at all, optimization is less important to me in this project as I am still learning the basics of graphics programming.

For code reference I am relying a lot on [Raytracing in a weekend](https://raytracing.github.io/) but trying to rewrite it and implement it into a standalone GUI app, in an attempt to better understand how the raytracing algorithms work. I learn best from practice, and so I hope to start more projects around graphical coding in the future. Everytime I work on this project I feel like I am learning a lot, so regardless of how messy it might end up, I think it's a worthwhile effort!

I hope this project turns out well!

## Planned features:

- ✅ Raytrace rendering
- ✅ Camera
- ✅ Shadows
- ✅ Antialiasing
- ✅ Lambert material
- ❌ Metal material
- ❌ Dialectric material
- ❌ Depth-of-field
<br/>

- ❌ UI: Outliner
- ✅ UI: Viewport
- ❌ UI: Property Editor
- ❌ UI: Material Editor
- ❌ UI: Camera/Render Editor

Potential features if it's not too difficult:

- ✅ Rendering in-viewport
- ❌ Preview rendering with dynamic sampling
- ❌ Support for Android
<br/>

---

<br/>
<br/>

---

# Blog

Timegaps are mostly because of breaks, I work on this on my free time next to work and I sometimes don't want to stare at code every day non stop. ^^

## Day 0 | Mockup of the UI:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/UI_Mockup.png)

Before starting, I try to plan for the final functionality. To summarize, the Bubbles GUI must allow the user to create new objects, manipulate these objects, create and modify materials, an outliner for both the materials and objects to keep an easy overview. The viewport must be able to show a live updating preview of the final scene, and there must be controls to modify the live preview. Finally it needs to be able to render the final image. First priority: getting it to render anything at all. :P 

For funsies I made a cute icon and a banner for the project!! 

---

## Day 4 | First working UI:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/first_ui.jpg)

This UI is very barebones and not very pretty. The renderbutton does work however, and it will render an image outputted by the raytracing function. This image can be updated and thus provides the basis to create the live updating viewport. The next target is to introduce more advanced raytracing functionality and experiment with how the performance keeps up, and finding potential problems that need to be solved.

Getting the UI to work took a bit of effort as this is my first time using the Qt framework in C++. Thankfully I managed to figure it out after research and it's working as I originally intended. It was easier than I originally anticipated, probably because I often overcomplicate these sorts of things..

---

## Day 5 | Raytracing, normals and object-oriented:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/first_raytrace.jpg)

Normals are calculated and displayed as image and there is a scene object, as well as a list of objects that can be added to easily. I don't think I have a lot else to write. Oh! The colours in normals are actually really funny. The reason the colours of normal maps are the way they are, is because if you plug in the X, Y, and Z of the normal-vector into R, G, B, you get those colours as result! Pretty basic stuff I suppose, but it blew my mind a little haha.

---

## Day 13 | Diffuse renderingggg:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/first_diffuse.jpg)

Diffuse rendering is now implemented, along with more GUI setup stuffs. I'm noticing that I need to restructure some of the code, mostly around the scene and objects side of things. The scene object will be containing the camera and all the materials and bubbles in the scene. Image/render related settings, such as image size, I'll probably store as static global variables that can be passed to the raytracing function. Before this, all this info was in the scene class itself, which made it messy to adjust those values. Learning moment!!

Once the materials are working, I'll start more seriously streamlining this part of the program, so it can be modified by the UI without code that is _too_ messy...

---

## Day 15 | Materials, camera, and scene objects:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/materials.jpg)

There are now 3 types of materials: Lambert, Metallic, Dielectric. Lamberts only have a simple albedo colour variable, the metallic have a albedo colour and a roughness variable, and the dielectric material simply has an index of refraction.

The camera has also been reworked and it can now be blurry! The current next goal is to create a better management for the scene, and create easy functions so I can hook up the GUI interface without too much hassle.