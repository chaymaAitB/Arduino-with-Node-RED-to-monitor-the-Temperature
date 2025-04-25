# 🌡️ Arduino with Node-RED to Monitor the Temperature

This project demonstrates how to read temperature data from a **DHT11 sensor** using an **Arduino Uno** and visualize it in real-time using **Node-RED**.

---

## 🧰 Components Required

### 🔌 Hardware
- Arduino Uno  
- DHT11 Temperature & Humidity Sensor  
- Female-to-Male Jumper Wires  
- USB Cable

### 💻 Software
- Arduino IDE  
- Node.js  
- Node-RED  

---

## 🧭 Circuit Diagram

The circuit diagram was drawn using **Fritzing software**.

📷 *Insert circuit diagram here*  
**(picture1)**

- **VCC** → **3.3V** on Arduino  
- **GND** → **GND** on Arduino  
- **DATA** → **Digital Pin 2**

I used **female-to-male jumper wires** for easy connections. The setup is powered via USB.

---

## 🧑‍💻 Arduino Code Explanation: `temp.ino`

This code reads temperature data from the DHT11 sensor and sends it over the serial port.

### 🧩 Libraries & Initialization

```cpp
#include <DHT.h>

#define DHTPIN 2         // Pin where the DHT is connected
#define DHTTYPE DHT11    // DHT 11

DHT dht(DHTPIN, DHTTYPE); // Initialize the DHT sensor
```

---

### ⚙️ Setup

```cpp
void setup() {
  Serial.begin(9600);
  dht.begin();
}
```

- Starts serial communication at 9600 baud  
- Initializes the sensor

---

### 🔁 Loop

```cpp
void loop() {
  float T = dht.readTemperature(); 

  if (isnan(T)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(String(T, 2));
  Serial.print("\n");
  delay(2000);
}
```

- Reads temperature in Celsius  
- Prints the temperature every 2 seconds  
- Handles errors when the sensor fails

🔌 Upload this code to your Arduino and open the **Serial Monitor** at **9600 baud** to view readings.

---

## 🌐 Setting up Node-RED

### 1️⃣ Install Required Nodes

Open a terminal and run the following commands:

```bash
npm install node-red-node-arduino
npm install node-red-node-serialport
npm install node-red-dashboard
```

---

### 2️⃣ Run Node-RED

Start Node-RED with:

```bash
node-red
```

Then open your browser and go to:

👉 [http://localhost:1880](http://localhost:1880)

📷 *Insert screenshot of Node-RED running*  
**(picture2)**

---

## 🔄 Creating a Flow in Node-RED: `flows.js`

Import the flow JSON file into Node-RED. This flow displays the temperature on the dashboard.

---

### 📦 Function Node Logic

```js
const bufferContext = context.get('bufferAccumulator') || Buffer.alloc(0);
let combinedBuffer;

if (msg.payload instanceof Buffer) {
    combinedBuffer = Buffer.concat([bufferContext, msg.payload]);
} else {
    combinedBuffer = Buffer.concat([bufferContext, Buffer.from(msg.payload.toString())]);
}

const newlineIndex = combinedBuffer.indexOf(10); // ASCII for '\n'

if (newlineIndex !== -1) {
    const completeMessage = combinedBuffer.slice(0, newlineIndex).toString().trim();
    context.set('bufferAccumulator', combinedBuffer.slice(newlineIndex + 1));

    const value = parseFloat(completeMessage);
    if (!isNaN(value)) {
        return { payload: value };
    }
} else {
    context.set('bufferAccumulator', combinedBuffer);
}

return null;
```

- Buffers incoming data chunks  
- Detects complete lines using `\n`  
- Parses and returns numeric temperature values

---

## 📊 Result

After deploying the flow, the dashboard displays the temperature in real time.

📷 *Insert dashboard screenshot here*  
**(picture3)**

---

## 🔗 References

- [IoT Design Pro: Arduino with Node-RED](https://iotdesignpro.com/projects/interface-arduino-with-node-red-to-send-sensor-data-on-webpage)
```

Let me know if you'd like this saved as a `.md` file or if you want help linking or visualizing the screenshots!
