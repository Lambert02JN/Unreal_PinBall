# Unreal_PinBall

A pinball game project developed with **Unreal Engine 4.26**. Players launch a ball, use the left and right flippers to keep it in play, and interact with bumpers and drop targets on the table.

This project is part of my game development portfolio. My contribution is the **game programming**. The visual assets used in the project were obtained from assets and were not created by me.

## Gameplay

Hold and release the launch key to send the ball onto the table. Use the flippers to redirect it and keep it from falling into the drain. The ball can trigger bumpers and knock down drop targets. When all targets in a set have been knocked down, they reset so play can continue.

The game also includes limited left and right tilt actions that apply an impulse to the ball. When a ball enters the drain, it is removed and a new ball is spawned.

## Controls

| Action | Key |
| --- | --- |
| Left flipper | Left mouse button or Left Ctrl |
| Right flipper | Right mouse button or Right Ctrl |
| Charge and release the plunger | Hold and release Space |
| Tilt left | Left Arrow |
| Tilt right | Right Arrow |

## Programming Features

- **Player input:** Maps keyboard and mouse input to the flippers, plunger, and tilt actions.
- **Flippers and plunger:** Handles flipper presses and releases, along with charging and releasing the ball launcher.
- **Ball and drain:** Spawns a ball at the plunger and spawns another after a drained ball is destroyed.
- **Table interactions:** Implements bumper reactions, drop targets, target-set resets, and related game events.
- **Tilt:** Applies a directional impulse to the ball and tracks the remaining uses.

The project includes C++ gameplay code in [`Source/PinBall`](Source/PinBall) and Unreal assets and Blueprints in [`Content`](Content).

## Built With

- Unreal Engine 4.26
- C++
- Unreal Engine Blueprints

## Run the Project

1. Clone or download this repository.
2. Open `PinBall.uproject` with Unreal Engine 4.26.
3. If prompted, allow Unreal Engine to build the C++ project modules.
4. Open `MainMap` and press **Play**.

## Portfolio Contribution and Asset Attribution

I wrote the gameplay programming for this project. The art assets, including visual elements and any character assets or animations used, came from assets and are **not my original artwork**. This portfolio entry is intended to demonstrate my technical work rather than claim authorship of those assets.

**Repository:** https://github.com/Lambert02JN/Unreal_PinBall
