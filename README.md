![image](https://github.com/MaxineCodes/Bubbles/blob/master/Bubbles/img/banner.png)

# Bubbles Raytracing Renderer
 
The Bubbles raytracing rendering engine is a GUI offline raytracing engine project which only renders `Bubbles` (spheres) using C++. <br/>
Qt is used for the GUI. 2D graphics & icons are made with Adobe Illustrator.

The Bubbles app will be a relatively simple 3D DCC program, where you can place spheres around the scene, assign materials, and render a final image. <br/>
My focus on this project is to get it to work at all, optimization is less important to me in this project as I am still learning the basics of graphics programming. <br/>
I hope this project turns out well!!

## Planned features:

- ❌ Raytrace rendering
- ❌ Camera
- ❌ Shadows
- ❌ Antialiasing
- ❌ Lambert material
- ❌ Metal material
- ❌ Dialectric material
- ❌ Depth-of-field
<br/>

- ❌ UI: Outliner
- ❌ UI: Viewport
- ❌ UI: Property Editor
- ❌ UI: Material Editor
- ❌ UI: Camera/Render Editor

Potential features if it's not too difficult:

- ❌ Rendering in-viewport
- ❌ Preview rendering with dynamic sampling
- ❌ Support for Android/iOS
<br/>

---

<br/>
<br/>

---

# Blog


## Mockup of the UI:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/UI_Mockup.png)

Before starting, I try to plan for the final functionality. To summarize, the Bubbles GUI must allow the user to create new objects, manipulate these objects, create and modify materials, an outliner for both the materials and objects to keep an easy overview. The viewport must be able to show a live updating preview of the final scene, and there must be controls to modify the live preview. Finally it needs to be able to render the final image. First priority: render preview!

For funsies I made a cute icon and a banner for the project!! 

---

## First working UI:

![image](https://github.com/MaxineCodes/Bubbles/blob/master/Blog/first_ui.jpg)

This UI is very barebones and not very pretty. The renderbutton does work however, and it will render an image outputted by the raytracing function. This image can be updated and thus provides the basis to create the live updating viewport. The next target is to introduce more advanced raytracing functionality and experiment with how the performance keeps up, and finding potential problems that need to be solved.

Getting the UI to work took a bit of effort as this is my first time using the Qt framework in C++. Thankfully I managed to figure it out after research and it's working as I originally intended. It was easier than I originally anticipated, probably because I often overcomplicate these sorts of things..

---

