# 🔢 Keypad Calculator (Arduino Mega + 4x4 Keypad)

This project is a **mini calculator** built using an **Arduino Mega** and a **4x4 Keypad**.  
It demonstrates keypad scanning, handling multi-digit inputs, and performing basic arithmetic operations.  
The project is fully **simulatable on Wokwi**, so you can try it online without hardware.

---

## ✨ Features

- Supports **multi-digit input** (up to 4 digits).  
- Arithmetic operations:  
  - `A` → Addition  
  - `B` → Subtraction  
  - `C` → Multiplication  
  - `D` → Division  
- Uses `*` to terminate numbers shorter than 4 digits.  
- Displays results directly on the connected **7-segment display**.  
- Handles division by zero and large numbers gracefully (shows `EEEE` if the result is out of range).  

---

## 🛠️ How It Works

1. Enter the **first number** using the keypad.  
   - If the number has fewer than 4 digits, press `*` to finish entry.  
2. Choose an **operation key**:  
   - `A` = +  
   - `B` = -  
   - `C` = ×  
   - `D` = ÷  
3. Enter the **second number** (again, `*` if less than 4 digits).  
4. The result will be calculated and displayed on the 7-segment display.  

---

## 🚀 Run on Wokwi

You don’t need real hardware — just open it in Wokwi!

🔗 **Live Simulation:** [Wokwi Project Link](https://wokwi.com/projects/439906558184236033)

Or run it yourself:
1. Go to [Wokwi](https://wokwi.com/).  
2. Upload `diagram.json`, `sketch.ino`, and `helper.h`.  
3. Start the simulation.  
4. Use the keypad to perform calculations!  

---

## 📂 Files in Repository

- `sketch.ino` → Main Arduino code  
- `helper.h` → Helper functions for calculations  
- `diagram.json` → Wokwi circuit setup  
- `README.md` → Project documentation  

---


## 📜 License

This project is licensed under the **MIT License**.  
Feel free to use and modify it for your own projects.  


