## 1️⃣ Compile both programs

Open **two terminals** (or two tabs).

### Compile the server

```bash
gcc server.c -o server
```

### Compile the client

```bash
gcc client.c -o client
```

(Replace `server.c` / `client.c` with your actual filenames.)

---

## 2️⃣ Run the server (Terminal 1)

Start the server **first** and give it a port number:

```bash
./server 5000
```

The server will now **wait for a client connection**.

---

## 3️⃣ Run the client (Terminal 2)

Connect to the server using IP and port:

```bash
./client 127.0.0.1 5000
```

- `127.0.0.1` → localhost (same machine)
- `5000` → must match the server port

---

## 4️⃣ Test it

1. Type a message in the **client terminal**

   ```
   hello
   ```

2. Press **Enter**
3. Server reverses it and sends back:

   ```
   olleh
   ```

---

## 🔁 What’s happening internally

| Step | Program | Action                            |
| ---- | ------- | --------------------------------- |
| 1    | Server  | `socket → bind → listen → accept` |
| 2    | Client  | `socket → connect`                |
| 3    | Client  | sends string                      |
| 4    | Server  | reverses string                   |
| 5    | Server  | sends back                        |
| 6    | Client  | receives & prints                 |

---

## ⚠ Common mistakes

❌ Server not started first
❌ Port numbers don’t match
❌ Firewall blocking port
❌ Using wrong IP (use `127.0.0.1` for same machine)
