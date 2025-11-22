# glau
(hopefully) lightweight abstraction layer for OpenGL, GLFW and miniaudio.

## Introduction

> [!note]
> This project is still in development.

This library aims to provide a lightweight abstraction layer around OpenGL,
GLFW and miniaudio. We might add a Metal abstraction in a very late, very
hypothetical future. `glau` is divided in interoperable parts:

- `glaufw`: independent layer that abstracts GLFW.
- `glaugl`: independent layer that abstracts OpenGL 4.5. It doesn't force any
  specific context, so you can provide any library you want.

Next on the roadmap:

- `glauv`: backend-agnostic high-level 3d graphics API. We aim to provide a
  `glaugl` backend for now, but also we want to enable users to write a custom
  backend if they want to.
- `glaudio`: independent layer that abstracts miniaudio
