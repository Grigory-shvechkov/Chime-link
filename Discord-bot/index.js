require('dotenv').config({ path: '../.env' }); // load .env

const { Client, GatewayIntentBits } = require("discord.js");
const axios = require("axios"); // for HTTP requests

// ---- CONFIG ----
const TOKEN = process.env.DISCORD_TOKEN;      // Discord bot token from .env
const ESP_IP = "192.168.17.69";               // ESP32 IP address
const ESP_URL = `http://${ESP_IP}/ping`;      // endpoint to ping

// ---- CREATE DISCORD CLIENT ----
const client = new Client({
  intents: [
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages,
    GatewayIntentBits.MessageContent,
  ],
});

// ---- BOT READY ----
client.once("ready", () => {
  console.log("Bot is online ✅");
});

// ---- MESSAGE HANDLER ----
client.on("messageCreate", async (message) => {
  if (message.author.bot) return;

  // ---- TEST COMMAND ----
  if (message.content === "!test") {
    message.reply("It works 🎉");

    try {
      const res = await axios.get(ESP_URL);
      console.log("ESP Response:", res.data);  // should log "pong"
    } catch (err) {
      console.error("Error contacting ESP32:", err.message);
      message.reply("⚠️ Could not reach the ESP32!");
    }
  }

  // ---- FUTURE COMMAND: PLAY CHIME ----
  if (message.content === "!chime") {
    try {
      const res = await axios.get(`http://${ESP_IP}/chime`);
      console.log("ESP Response:", res.data);
      message.reply("🔔 Chime triggered on ESP32!");
    } catch (err) {
      console.error("Error contacting ESP32:", err.message);
      message.reply("⚠️ Could not trigger chime on ESP32!");
    }
  }
});

// ---- LOGIN ----
client.login(TOKEN);
