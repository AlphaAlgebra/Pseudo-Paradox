cd ~/Pseudo-Paradox

cat << 'EOF' > frontend/src/api/websocket.js
export class QuantumStreamClient {
    constructor(serverUrl, onDataReceived) {
        this.serverUrl = serverUrl;
        this.onDataReceived = onDataReceived;
        this.socket = null;
        this.autoReconnect = true;
    }

    connect() {
        console.log(`// ESTABLISHING CONNECTION TO QUANTUM CORE: ${this.serverUrl} //`);
        this.socket = new WebSocket(this.serverUrl);

        this.socket.onopen = () => {
            console.log("// DATA ENGINE LINK ENERGINED //");
        };

        this.socket.onmessage = (event) => {
            try {
                const packet = JSON.parse(event.data);
                if (packet.status === "EIGENFLOW_ACTIVE" && this.onDataReceived) {
                    this.onDataReceived(packet.geometry);
                }
            } catch (err) {
                console.error("// PACKET DECOMPRESSION FAULT //", err);
            }
        };

        this.socket.onclose = () => {
            console.warn("// CORE LINK SEVERED //");
            if (this.autoReconnect) {
                console.log("// COOLDOWN ACTIVE: RETRYING CONNECTION IN 3S //");
                setTimeout(() => this.connect(), 3000);
            }
        };

        this.socket.onerror = (error) => {
            console.error("// STREAM LINE EXCEPTION TRAPPED //", error);
        };
    }

    disconnect() {
        this.autoReconnect = false;
        if (this.socket) {
            this.socket.close();
        }
    }
}
EOF
