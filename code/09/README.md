# ✅ HOW TO COMPILE

```bash
gcc server.c -o server
gcc client.c -o client
```

---

# ✅ HOW TO RUN

### 1️⃣ Start server

```bash
./server 5000
```

(5000 = port number)

---

### 2️⃣ Run clients (in different terminals)

```bash
./client 127.0.0.1 5000
```

You can open multiple terminals and run client multiple times.

---

# ✅ HOW IT WORKS

- Server:
  - Uses `select()` to monitor multiple sockets
  - Accepts new connections
  - Broadcasts received messages to all other clients

- Client:
  - Uses `select()` to monitor:
    - Keyboard (stdin)
    - Socket

  - Sends typed message to server
  - Displays received messages

---

# 🎯 Final Result

You now have a working **multi-client chat server using TCP and select()**.
