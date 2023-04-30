# Dots And Boxes Input Programs

<!---### Authors:-->

## Game Descripton

https://en.wikipedia.org/wiki/Dots_and_boxes

<!---## How to use-->



## Input Programs Guide:
- v1: OUTDATED (only for reference) very very basic implementation that plays the first blank move that it finds (no logic)
  - v1.1: fixed v1 (dynamic board sizes and 0,0 is bottom left)
  - v1.2: very very basic implementation that plays a random move
- v2: uses basic game logic but does not check neighbors
  - v2.1: fixed v2 (dynamic board sizes and 0,0 is bottom left)
  - v2.2: same logic as v1.1 but checks adjacent square before playing move
- v3: extremely broken alpha-beta

## squares.board Guide
- Fist line of file is a single digit n that represents the board size (ex. 6 would represent 6 by 6 square board)
- Next n lines each have n struct representations as follows: 

{bool top, bool right, bool bottom, bool left,  string owner}

  - bool values:
      - 1 = played
      - 0 = blank
  - owner values:
      - red
      - blue 
      - none


## Other Notes
- Add line to top of file for visual studios compilation: #define _CRT_SECURE_NO_WARNINGS
