# Chime-Link

Chime-Link is a **Discord-controlled door chime system** powered by an **ESP32**.  
It allows students to trigger a physical signal (LEDs and optional audio) by sending commands through a Discord bot.

---

## Project Purpose

This project was created for the **University of Massachusetts Makerspace** to make it easier for students to access the building.

**The problem**
- The makerspace building locks automatically
- Students must rely on **pinging staff** to unlock the door

**The solution**
- Chime-Link **automates the response**
- Students trigger a door chime system via Discord
- The ESP32 receives the signal and runs a visible (and extendable) hardware sequence

This reduces delays, removes friction, and improves accessibility for students.

---

## Features

- Discord bot command interface
- ESP32 HTTP server for local triggers
- Configurable LED sequence
- Secure environment variable handling
- Easily extendable to buzzers, speakers, relays, or door hardware

---

## Hardware Requirements

- ESP32 development board
- 3 LEDs: **Red, Green, Yellow**
- 3 × 220Ω resistors
- Breadboard + jumper wires

**Wiring**
- GPIO → LED (anode)
- LED (cathode) → 220Ω resistor → GND
---

## Software Requirements

### Node.js
- Node.js v18 or newer  
Download from: https://nodejs.org

### PlatformIO (ESP32)
- Recommended IDE for flashing ESP32
- Works in VS Code

---

## Installation

### 1. Clone the repository

```bash
git clone https://github.com/Grigory-shvechkov/Chime-link.git
cd Chime-link
```

## Discord Bot Setup

This project uses a Discord bot to send HTTP requests to the ESP32 when commands are issued in a server.

---

### 1. Create a Discord Application

1. Go to the Discord Developer Portal  
   https://discord.com/developers/applications
2. Click **New Application**
3. Name it (e.g. `Chime-Link`)
4. Navigate to **Bot** → Click **Add Bot**

---

### 2. Configure the Bot

- Enable:
  - **Message Content Intent**
- Disable:
  - Public bot (optional, recommended for private servers)

Save changes.

---

### 3. Copy the Bot Token

- In the **Bot** tab, click **Reset Token**
- Copy the token
- Store it in your `.env` file

```env
DISCORD_TOKEN=your_discord_bot_token_here
```

## How to Run Chime-Link


### 1. Start the ESP32

1. Flash the ESP32 with the code in `main.cpp`
2. Open the Serial Monitor
3. Wait for:
   - WiFi connection
   - ESP32 IP address
   - HTTP server started

Make sure the ESP32 stays powered on.


### 2. run index.js 
run `npm index.js`

### 3. Send commands

1. `!chime` You should see the LED's light up
2. or `!test` You should get a message that the esp has recived your message
