# 🧨 Minesweeper Game in C++

This is a console-based **Minesweeper** game implemented in C++ using **Object-Oriented Programming (OOP)**. The game allows you to play on a 15x15 grid with three difficulty levels: Easy, Medium, and Hard.

---

## 🎮 Features

- 15x15 grid-based board
- Difficulty levels:
  - **Easy** – 10 mines
  - **Medium** – 40 mines
  - **Hard** – 99 mines
- Timer to track play duration
- Flagging system to mark suspected mines
- Recursive reveal of empty (`0`) cells
- Game ends upon revealing a mine or clearing all safe cells
- Reveals all mines when the game ends
- Clean and modular OOP structure with abstract base class and polymorphism

---

## 🛠 How It Works

### Controls

- Input a **row** and **column** (0-indexed)
- Enter:
  - **`L`** to reveal a cell
  - **`R`** to flag a cell as a mine

### Game Logic

- The board is initialized with:
  - Random mine (`*`) placements
  - Random characters (`1-9` and `0`) to simulate surrounding mine counts
- Revealing a `0` cell opens up surrounding cells recursively
- Flagged cells can’t be revealed unless unflagged first
- Timer starts when the game begins and is displayed after each move

---

## 📂 File Structure

- `game` (abstract base class): Core logic for gameplay, user input, timer, board display
- `easy`, `medium`, `hard` classes: Inherit from `game`, set difficulty-specific mine and value distribution
- `main`: Starts the game and lets user pick a difficulty

---

## 🚀 How to Compile and Run

### Requirements

- C++ compiler (like `g++`)

