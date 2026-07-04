import { QuantumWorld } from './world/Scene.js';
import { QuantumMesh } from './world/MeshGeometry.js';
import { QuantumStreamClient } from './api/websocket.js';

// Initialize the 3D graphics canvas context
const world = new QuantumWorld();

// Scaffold out the 3D landscape lines mesh 
const quantumMesh = new QuantumMesh(world.scene);

// Connect your WebSocket client directly to the running backend data stream
const streamClient = new QuantumStreamClient(
    "ws://127.0.0.1:8000/ws/quantum-flow", 
    (incomingGeometryPackets) => {
        quantumMesh.updateMeshTopology(incomingGeometryPackets);
    }
);
streamClient.connect();

// Continuous animation loop pipeline
function animate(timestamp) {
    requestAnimationFrame(animate);
    world.render(timestamp);
}

// Spark up the engine
requestAnimationFrame(animate);
console.log("// PSEUDO-PARADOX V1 ENGINE ACTIVATED SUCCESSFULLY //");
