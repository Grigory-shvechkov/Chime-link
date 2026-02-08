require('dotenv').config({path: '../.env'}); // <-- load .env file

const { Client, GatewayIntentBits } = require("discord.js");

const client = new Client({
  intents: [
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages,
    GatewayIntentBits.MessageContent,
  ],
});

// Load token from environment variable
const TOKEN = process.env.DISCORD_TOKEN;

client.once("ready", () => {
  console.log("Bot is online ✅");
});

client.on("messageCreate", (message) => {
  if (message.author.bot) return;

  if (message.content === "!test") {
    message.reply("It works 🎉");
  }
});

// Login with token from .env
client.login(TOKEN);
