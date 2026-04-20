<div align="center">

```
 #############################################################################################
 #   ___   ___  ________  ______  ___   ___       ______  ___   ___  ________  _________   #
 #  /__/\ /__/\/_______/\/_____/\/__/\ /__/\     /_____/\/__/\ /__/\/_______/\/________/\  #
 #  \::\ \\  \ \::: _  \ \::::_\/\::\ \\  \ \    \:::__\/\::\ \\  \ \::: _  \ \__.::.__\/  #
 #   \::\/_\ .\ \::(_)  \ \:\/___/\::\/_\ .\ \    \:\ \  _\::\/_\ .\ \::(_)  \ \ \::\ \   #
 #    \:: ___::\ \:: __  \ \_::._\:\:: ___::\ \    \:\ \/_/\:: ___::\ \:: __  \ \ \::\ \   #
 #     \: \ \\::\ \:.\  \ \ \/____\:\: \ \\::\ \    \:\_\ \ \: \ \\::\ \:.\  \ \ \ \::\ \  #
 #      \__\/ \::\/\__\/\__\/\_____\/\__\/ \::\/     \_____\/\__\/ \::\/\__\/\__\/  \__\/  #
 #                                                                            By Awais      #
 #############################################################################################
```

# 🔐 Encrypted Chat System

**A secure, terminal-based client-server chat application implementing real-world cryptographic protocols**

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)](https://isocpp.org/)
[![Security](https://img.shields.io/badge/Encryption-AES--128--CBC-green?style=for-the-badge&logo=openssh)](https://www.openssl.org/)
[![Protocol](https://img.shields.io/badge/Key_Exchange-Diffie--Hellman-orange?style=for-the-badge)](https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange)
[![Hashing](https://img.shields.io/badge/Hashing-SHA--256-red?style=for-the-badge)](https://en.wikipedia.org/wiki/SHA-2)
[![Platform](https://img.shields.io/badge/Platform-Linux-yellow?style=for-the-badge&logo=linux)](https://www.linux.org/)

</div>

---

## 📋 Table of Contents

- [About The Project](#-about-the-project)
- [Key Features](#-key-features)
- [System Architecture](#-system-architecture)
- [Cryptographic Concepts](#-cryptographic-concepts)
- [File Structure](#-file-structure)
- [Prerequisites](#-prerequisites)
- [Installation & Usage](#-installation--usage)
- [How It Works](#-how-it-works)
- [Security Mechanisms](#-security-mechanisms)
- [Admin Panel](#-admin-panel)
- [Screenshots](#-screenshots)
- [Author](#-author)

---

## 🎯 About The Project

The **Encrypted Chat System** is an **Information Security** project that demonstrates the practical implementation of cryptographic protocols used in real-world secure communication systems such as WhatsApp, Signal, and HTTPS.

This project was developed to show how modern applications protect user data through:

- Secure key negotiation between two parties over an insecure channel
- Military-grade message encryption
- Safe credential storage using industry-standard hashing
- Role-based access control with a privileged admin system

> *"Every time you send a WhatsApp message, something very similar to this happens behind the scenes."*

---

## ✨ Key Features

| Feature | Description |
|--------|-------------|
| 🔑 **Diffie-Hellman Key Exchange** | Secure shared key generation without transmitting the key |
| 🔒 **AES-128-CBC Encryption** | Military-grade encryption for all chat messages |
| 🧂 **Salted SHA-256 Hashing** | Passwords never stored in plain text |
| 👮 **Role-Based Access Control** | Separate User and Admin privilege levels |
| 🌐 **Socket Programming** | Real TCP/IP client-server communication |
| 🔁 **Multi-Client Support** | Server handles multiple clients via `fork()` |
| 🛡️ **Brute-Force Tracking** | Failed login attempt counter |
| 📁 **Persistent Storage** | User credentials saved across sessions |

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                      CLIENT SIDE                        │
│                                                         │
│   ┌──────────┐    ┌──────────┐    ┌─────────────────┐  │
│   │  User    │    │ Caesar   │    │  AES-128-CBC    │  │
│   │  Input   │───►│ Cipher   │───►│  Encryption     │  │
│   │          │    │ (Auth)   │    │  (Chat)         │  │
│   └──────────┘    └──────────┘    └────────┬────────┘  │
│                                            │           │
└────────────────────────────────────────────┼───────────┘
                                             │ TCP Socket
                         ┌───────────────────▼───────────┐
                         │     NETWORK (Port 8080)        │
                         │   Encrypted Data Travels Here  │
                         └───────────────────┬───────────┘
                                             │
┌────────────────────────────────────────────┼───────────┐
│                      SERVER SIDE           │           │
│                                            │           │
│   ┌──────────┐    ┌──────────┐    ┌────────▼────────┐  │
│   │ State    │    │ SHA-256  │    │  AES-128-CBC    │  │
│   │ Machine  │◄───│ Verifier │◄───│  Decryption     │  │
│   │          │    │          │    │                 │  │
│   └──────────┘    └──────────┘    └─────────────────┘  │
│                                                         │
│   ┌─────────────────────────────────────────────────┐   │
│   │              updated_creds.txt                  │   │
│   │   username | email | salt | SHA256_hash         │   │
│   └─────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

---

## 🔐 Cryptographic Concepts

### 1. Diffie-Hellman Key Exchange

Both parties generate a **shared secret key** over a public channel without ever transmitting the key itself.

```
Public Values:  P = 17 (prime),  α = 2 (generator)

Server:                          Client:
Private key (a) = 2              Private key (b) = 3

Public key A = α^a mod P         Public key B = α^b mod P
             = 2^2 mod 17                     = 2^3 mod 17
             = 4                              = 8

──────── Exchange Public Keys ────────

Shared Key (Server) = B^a mod P  Shared Key (Client) = A^b mod P
                    = 8^2 mod 17                     = 4^3 mod 17
                    = 4                              = 4

         ✅ Both arrive at the SAME shared key = 4
              WITHOUT ever sending it!
```

### 2. AES-128-CBC Encryption

Each chat message is encrypted using **AES-128-CBC** — the same standard used by banks and governments.

```
Plaintext:   "Hello Server!"
    +
Random IV:   [16 random bytes generated per message]
    +
Key:         [Derived from DH shared key]
    │
    ▼
AES-128-CBC Encryption
    │
    ▼
Ciphertext:  "ßØ∂ƒ©˙∆˚¬…" ← Unreadable gibberish on network
    │
    ▼ (at receiver)
AES-128-CBC Decryption (same key)
    │
    ▼
Plaintext:   "Hello Server!" ✅
```

### 3. Salted SHA-256 Password Hashing

Passwords are **never stored in plain text**. A random salt is added before hashing to prevent rainbow table attacks.

```
Password:    "MyPass@123"
Salt:        "xK9mPqR2AbCd7Ef1"  ← Random, unique per user
    │
    ▼
SHA-256("MyPass@123" + "xK9mPqR2AbCd7Ef1")
    │
    ▼
Stored Hash: "8d48a9681b6cf5ecbb1af00b..." ← This is what gets saved
```

---

## 📁 File Structure

```
Encrypted-Chat-System/
│
├── 📄 server.cpp           # Main server — handles all clients
├── 📄 client.cpp           # Main client — user interface & communication
│
├── 📄 HEADER.h             # AES encryption/decryption functions + UI banners
├── 📄 ADMIN.h              # Admin class — user management & privileges
├── 📄 user.h               # User class — registration, validation, hashing
│
├── 📄 deffie_helmin.cpp    # Diffie-Hellman brute force demonstration
├── 📄 key_exchange_mec.cpp # DH key exchange mechanism (standalone demo)
│
├── 📄 updated_creds.txt    # Secure credential storage (salted SHA-256)
├── 📄 creds.txt            # Raw registration log
├── 📄 admin_pass.txt       # Admin credentials (hashed)
│
├── 📄 TRAFFIC_CAPTURED.pcapng  # Wireshark packet capture (demonstration)
└── 📄 README.md            # This file
```

---

## ⚙️ Prerequisites

Make sure the following are installed on your Linux system:

```bash
# GCC Compiler
sudo apt install g++

# OpenSSL Library (for AES & SHA-256)
sudo apt install libssl-dev

# Verify installation
openssl version
g++ --version
```

---

## 🚀 Installation & Usage

### Step 1 — Clone / Download the Project

```bash
cd ~/your-folder/Encrypted-Chat-System-main
```

### Step 2 — Compile Both Files

```bash
# Compile Server
g++ server.cpp -o server -lssl -lcrypto

# Compile Client
g++ client.cpp -o client -lssl -lcrypto
```

### Step 3 — Run the System

Open **two terminals** side by side:

```bash
# ── Terminal 1 (Server) ──
./server
```

```bash
# ── Terminal 2 (Client) ──
./client
```

### Step 4 — Choose Your Action

```
=> [1] NEW TO CHAT? REGISTER NOW.
=> [2] OLD ONE? LOGIN.
=> [3] {ADMIN} Super_User?
=> [0] EXIT.
```

---

## ⚙️ How It Works

### Complete Flow Diagram

```
CLIENT STARTS
     │
     ▼
Connect to Server (Port 8080)
     │
     ▼
┌─── Diffie-Hellman Handshake ───┐
│  Server sends P, α, pub_key    │
│  Client computes & sends pub   │
│  Both compute SAME shared key  │
└────────────────────────────────┘
     │
     ▼
Show Menu
     │
     ├──[1]── REGISTER
     │           │
     │        Enter Username (unique check)
     │        Enter Email    (format check)
     │        Enter Password (strength check)
     │        Salt generated → SHA-256 → saved
     │
     ├──[2]── LOGIN
     │           │
     │        Enter Username + Password
     │        SHA-256(input+salt) == stored hash?
     │           │
     │        YES → Enter CHAT mode
     │           │
     │        AES encrypt message → send
     │        Receive → AES decrypt → display
     │
     ├──[3]── ADMIN LOGIN
     │           │
     │        Verify admin credentials
     │        Access Admin Panel
     │
     └──[0]── EXIT
```

---

## 🛡️ Security Mechanisms

| Attack Type | Protection Used |
|-------------|----------------|
| Eavesdropping (Man in Middle) | AES-128-CBC Encryption |
| Password Theft | Salted SHA-256 Hashing |
| Rainbow Table Attack | Unique Salt per User |
| Key Interception | Diffie-Hellman Exchange |
| Replay Attack | Random IV per Message |
| Weak Passwords | Strong Password Policy |
| Brute Force Login | Attempt Counter Tracking |

### Password Policy
Passwords must contain:
- ✅ At least **1 uppercase** letter (A-Z)
- ✅ At least **1 lowercase** letter (a-z)
- ✅ At least **1 digit** (0-9)
- ✅ At least **2 special characters** (!@#$%^&*)

---

## 👮 Admin Panel

The admin has elevated privileges to manage the entire system:

```
┌─────────────────────────────────────────┐
│              { ADMIN MENU }             │
│ ─────────────────────────────────────── │
│ 1. UPDATE Admin Data                    │
│ 2. VIEW Admin Information               │
│ 3. EDIT Admin Information               │
│ 4. REMOVE a User                        │
│ 5. VIEW All Users (Hashed Passwords)    │
│ 6. VIEW All Users (Registration Info)   │
│ 7. EXIT Menu                            │
└─────────────────────────────────────────┘
```

**To reset admin password:**
```bash
g++ reset_admin.cpp -o reset_admin -lssl -lcrypto
./reset_admin
```

---

## 🖥️ Screenshots

```
Server Running:                    Client Connected:
─────────────────                  ─────────────────
LISTENING ON PORT 8080             HASH CHAT Banner
                                   => [1] Register
NEW USER REGISTERED ✓              => [2] Login
                                   => [3] Admin
[CLIENT] => Hello!                 => [0] Exit
[SERVER] => Hi there!
```

---

## 🔬 Bonus — Standalone Demos

### Key Exchange Demo
```bash
g++ key_exchange_mec.cpp -o key_demo
./key_demo
# Shows DH exchange step by step
```

### Brute Force Demo
```bash
g++ deffie_helmin.cpp -o brute_demo
./brute_demo
# Enter a shared key — it finds the parameters
```

---

## 📚 Concepts Reference

| Concept | Real World Use |
|---------|---------------|
| Diffie-Hellman | HTTPS, TLS, SSH |
| AES-128-CBC | WhatsApp, Signal, VPNs |
| SHA-256 | Bitcoin, Passwords, Git |
| Salt + Hash | Every major login system |
| Socket Programming | All internet applications |
| Fork (multi-client) | Web servers (Apache, Nginx) |

---

## 👨‍💻 Author

**Awais**
*Information Security Project*
*Department of Artificial intelligence *

---

<div align="center">

**⭐ If this project helped you understand cryptography, consider starring it! ⭐**

*Built with ❤️ for Information Security*

</div>
