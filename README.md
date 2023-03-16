# Fractal
This project is a program written in C++ that can calculate the Mandelbrot set and display it on the screen. The program has the ability to zoom in and move around the set to explore its details. The implementation uses standard algorithms and formulas to accurately calculate the patterns that make up the set. The program is user-friendly and offers an immersive experience for those interested in exploring the Mandelbrot set.

## Libraries
- Simple and Fast Multimedia Library (SFML)
- Open Computing Language (OpenCL™)

## UML
```mermaid
---
title: Fractal
---
classDiagram
    SFML <-- InputManager
    
    Model <-- Viewer
    Model <-- Controller
    Model <-- InputManager
    Viewer <-- Controller
    Controller <-- InputManager
    
    SFML <-- Model
    SFML <-- Controller
    
    OpenCL_Kernel <-- Controller
    Mandelbrot <-- OpenCL_Kernel
    OpenCL <-- OpenCL_Kernel
    
    note for SFML "Is External Library"
    note for OpenCL "Is External Library"
    
    class Model{
        - xOffset: int
        - yOffset: int
        - zoom: int
        + Model(window: RenderWindow*)
        + getXOffset(): int
        + getYOffset(): int
        + getZoom(): int
        
        + changeZoomBy(amount: int): void
        + changeOffsetBy(ax: int, ay: int): void
        
        + dragxOffset: int
        + dragyOffset: int

        + lastxOffset: int
        + lastyOffset: int
        + lastzoom: int

        + MAX_ITERAIONS: int

        + window: RenderWindow*

        + scrolling: bool
        + lastScrolled: Clock
        + zoomChange: int

        + moving: bool
        + newPos: Vector2f
        + oldPos: Vector2f
        + deltaPos: Vector2f

        + frame: Texture
        + sprite: Sprite
        + actionSprite: Sprite
        + tMask: Color
    }
    
    class Viewer{
        - Model m
        + Viewer(m: Model* )
        + Draw(): void
    }
    
    class Controller{
        - m: Model*
        - v: Viewer*
        - image: Image;
        - kernel: OpenCL_Kernel*
        
        + Controller(m: Model*)

        + LoadImg(screen: Texture&): void
        + SaveImg(screen: Texture&): void
        + NeedToRedraw(): bool

        + Zoom(amount: int): void
        + ChangeOffset(x: int, y: int): void

        + Render(width: int, height: int): void

        + Exit(): void
    }
    
    class InputManager{
        - c: Controller*
	      - m: Model*
        
        + InputManager(c: Controller*, m: Model*)

	      + Handle(event: Event, window:Window&): void
    }
    
    class OpenCL_Kernel{
        + OpenCL_Kernel()

	      + Kernel(matriX: double*, matriY: double*, width: int, height: int, colors: int**): void
    }
    
    class Mandelbrot{
        + Kernel(width: int, height: int, matriX: __global double*, matriY: __global double*, colors: __global int*): __kernel void
    }
```
