# SpaceInvadersClone
C++ Space Invaders Clone

Working project to get back into C++.

## Implentation Aspects

Each line of enemies is stored in a single `unsigned integer` variable and each bit represents a single enemy ship
* `0` - there is no ship
* `1` - there is a ship

Since the bit size may vary, the most-left bit represents the first enemy ship at the left. The bits are traversed through from the left to the right.

## Libraries

The app uses SDL2 for graphics.

## Third-party images

All images used here were obtained either from screenshots of the original space invaders or from https://unsplash.com
