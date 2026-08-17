<div align="center">

# 🚀 SDL Space Shooter

### A ground-up C/SDL2 port of **Pyxel Space Shooter**

A retro-inspired space shooter rebuilt piece by piece in **C**, combining Atari-era arcade aesthetics with a modular SDL2 architecture.

![C](https://img.shields.io/badge/C-Programming-00599C?style=for-the-badge&logo=c&logoColor=white)
![SDL2](https://img.shields.io/badge/SDL2-2.30+-111111?style=for-the-badge)
![Linux](https://img.shields.io/badge/Linux-Mint-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Code::Blocks](https://img.shields.io/badge/IDE-Code%3A%3ABlocks-41AD48?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-In_Development-orange?style=for-the-badge)

**No sprites. No game engine. Just C, SDL2, procedural audio, and a suspiciously egg-shaped spaceship.**

</div>

---

## 🎮 About the Project

**SDL Space Shooter** is a C/SDL2 port of my original **Pyxel Space Shooter**, a retro-inspired arcade game built around the look and feel of classic Atari-era games.

Rather than translating the Python source line-by-line, this version is being **rebuilt from the ground up** as a hands-on C learning project. The goal is to recreate and improve the original while gaining practical experience with C project architecture, pointers, structs, header/source separation, SDL2 rendering and input, frame timing, object pools, collision handling, procedural audio, compilation, and linking.

---

## 🕹️ Current Features

| System | Status |
|:--|:--:|
| SDL2 window, renderer & game loop | ✅ |
| Player movement & screen boundaries | ✅ |
| Retro player ship | ✅ |
| Parallax starfield | ✅ |
| Bullet object pool | ✅ |
| Hold-to-fire & cooldown | ✅ |
| Procedural retro laser audio | ✅ |
| Enemy pool & timed spawning | ✅ |
| Scout enemies | ✅ |
| Bullet/enemy collision | ✅ |
| Enemy health & score tracking | ✅ |
| Modular C architecture | ✅ |
| Player damage / lives | ✅ |
| Player/Scout collision | ✅ |
| Timed post-hit invulnerability | ✅ |
| Blinking damage feedback | ✅ |
| Game states & restart behavior | ✅ |
| Custom 5×7 bitmap text renderer | ✅ |
| Retro Game Over screen | ✅ |
| Enemy weapons | 🚧 |
| Additional enemy types | 📋 |
| Asteroids / hazards | 📋 |
| HUD / bosses / power-ups | 📋 |

> 🚧 **Active development:** the game is a working prototype while systems from the original are ported and expanded.

---

## 🥚 The White Egg Ship

What began as a simple sprite-free player design somehow evolved into the **White Egg Ship**: a compact retro spacecraft with a light-blue cockpit, orange exhaust, and yellow projectiles.

Its primary weapon appears to fire high-velocity yolks.

**This was not in the original design document.**

---

## 🔊 Procedural 1983-Style Audio

The laser effect is generated **entirely in C** rather than loaded from an audio file. SDL2's audio callback receives generated waveform samples while the frequency slides downward to create a crunchy arcade-style **PEW**.

The system uses `SDL_OpenAudioDevice()`, `SDL_AudioSpec`, audio callbacks, generated sample buffers, and waveform synthesis.

No laser WAV required.

---

## 🧱 Project Architecture

The project began as a single `main.c` approaching **600 lines**. As systems became functional, they were extracted into dedicated modules. `main.c` is now primarily the game's orchestrator.

```text
sdl-space-shooter/
│
├── include/
│   ├── audio.h
│   ├── bullet.h
│   ├── collision.h
│   ├── enemy.h
│   ├── player.h
│   ├── starfield.h
│   └── text.h
│
├── src/
│   ├── audio.c
│   ├── bullet.c
│   ├── collision.c
│   ├── enemy.c
│   ├── player.c
│   ├── starfield.c
│   └── text.c
│
├── main.c
└── space_shooter.cbp
```

| Module | Responsibility |
|:--|:--|
| `player.c` | Player initialization, movement, boundaries, damage, invulnerability & rendering |
| `starfield.c` | Parallax stars, recycling & rendering |
| `bullet.c` | Bullet pool, firing, cooldown, movement & rendering |
| `enemy.c` | Enemy pool, Scout spawning, movement & rendering |
| `collision.c` | Bullet/enemy and player/enemy collision handling & score results |
| `audio.c` | SDL2 audio device & procedural laser synthesis |
| `text.c` | Built-in 5×7 bitmap font and scalable retro text rendering |
| `main.c` | SDL setup, game loop, game states, restart flow & system coordination |

---

## ⚙️ Tech Stack

| | |
|---|---|
| **Language** | C |
| **Graphics / Input / Audio** | SDL2 |
| **Audio** | Procedural waveform synthesis |
| **Development OS** | Linux Mint |
| **IDE** | Code::Blocks |
| **Compiler** | GCC |
| **Architecture** | Multi-file native C |

The current game uses **no sprite assets**. Ships, stars, enemies, and projectiles are drawn with SDL2 primitives.

---

## 🛠️ Building on Linux

For Debian / Ubuntu / Linux Mint:

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev
```

Verify SDL2:

```bash
pkg-config --modversion sdl2
pkg-config --cflags --libs sdl2
```

Typical compiler configuration:

```text
-Wall -g -Iinclude -I/usr/include/SDL2
```

Typical linker libraries:

```text
-lSDL2 -lm
```

The included `space_shooter.cbp` contains the Code::Blocks project configuration.

---

## 🧠 Why Port It to C?

The original game was written in **Python + Pyxel**. This port explores how those same systems work at a lower level.

| Python / Pyxel | C / SDL2 |
|:--|:--|
| Python objects | C structs |
| Dynamic collections | Fixed object pools |
| Methods | Functions + pointers |
| Python modules | `.c` + `.h` modules |
| Automatic references | Explicit pointers |
| Framework rendering | SDL2 renderer calls |
| Framework audio | SDL audio + generated samples |

> **The objective isn't simply to make the game work. The objective is to understand why it works.**

---

## 🗺️ Development Roadmap

### Foundation
- [x] SDL2 initialization
- [x] Window and renderer
- [x] Game loop
- [x] Keyboard input
- [x] Frame timing

### Player & Environment
- [x] Player movement
- [x] Screen boundaries
- [x] Retro ship rendering
- [x] Cockpit and exhaust
- [x] Scrolling parallax starfield

### Combat
- [x] Bullet object pool
- [x] Hold-to-fire
- [x] Fire cooldown
- [x] Procedural laser audio
- [x] Bullet/enemy collision

### Enemies
- [x] Enemy pool
- [x] Timed spawning
- [x] Scout enemy
- [x] Enemy health
- [x] Retro Scout graphics
- [x] Player/enemy collision
- [ ] Enemy attacks
- [ ] Additional enemy types

### Player Damage & Game States
- [x] Three-life player damage system
- [x] Timed post-hit invulnerability
- [x] Blinking invulnerability feedback
- [x] Prevent lives from dropping below zero
- [x] `GAME_PLAYING` and `GAME_OVER` states
- [x] Freeze gameplay on Game Over while keeping the starfield active
- [x] Restart with the R key
- [x] Reset player, bullets, enemies, score, and timers on restart

### UI & Text
- [x] Built-in 5×7 bitmap font
- [x] Scalable text renderer
- [x] Retro `GAME OVER` display
- [x] `PRESS R TO RESTART` prompt
- [ ] HUD and visible scoring
- [ ] Visible lives display

### Future
- [ ] Asteroids and hazards
- [ ] Enemy attacks
- [ ] Additional enemy types
- [ ] Power-ups and additional weapons
- [ ] Enemy destruction visual effects
- [ ] Enemy destruction sound
- [ ] Player destruction visual effect
- [ ] Player destruction sound
- [ ] Boss encounters
- [ ] Further graphics polish

---

## 🧪 Development Philosophy

Systems are deliberately built incrementally:

```text
Design the data
      ↓
Build the simplest working version
      ↓
Compile & test
      ↓
Refactor into a module
      ↓
Compile & test again
      ↓
Improve behavior and presentation
```

This keeps the project useful as both a playable project and a practical C learning exercise.

---

## 🐍 Original Python Version

This project is a ground-up C/SDL2 port of **Pyxel Space Shooter**, the original Python/Pyxel implementation that established the game's retro arcade direction.

The two implementations are maintained separately so the Python original and C port can exist side-by-side.

---

## 📸 Screenshots

Gameplay screenshots and captures will be added as development progresses.

<!--
<div align="center">
  <img src="docs/screenshots/gameplay.png" alt="SDL Space Shooter gameplay" width="700">
</div>
-->

---

## 🤝 Contributing

Suggestions, bug reports, and ideas are welcome. The project favors straightforward readable C, understandable module boundaries, minimal unnecessary dependencies, retro arcade presentation, and clarity over cleverness.

---

<div align="center">

### 🚀 Built the old-school way

**C · SDL2 · GCC · Linux**

*Rebuilding a tiny arcade universe one `.c` file at a time.*

⭐ **If you enjoy retro games, SDL2, or learning C through real projects, follow the project.**

</div>
