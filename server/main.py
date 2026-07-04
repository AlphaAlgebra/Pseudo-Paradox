from fastapi import FastAPI, WebSocket
import uvicorn
import asyncio
import json
import math

app = FastAPI(
    title="Pseudo-Paradox Core Streaming Engine",
    description="Orchestrates non-commutative matrix transformations and coordinate feeds."
)

@app.websocket("/ws/quantum-flow")
async def websocket_endpoint(websocket: WebSocket):
    await websocket.accept()
    print("// CLIENT INTEGRATED INTO QUANTUM STREAM //")
    
    t = 0.0
    try:
        while True:
            mesh_data = []
            grid_size = 20 # Coordinates matching our frontend grid definition
            
            # Map coordinates across space to stream down to Three.js
            for u in range(grid_size):
                for v in range(grid_size):
                    # Scale spatial coordinates centered at origin
                    x_coord = (u - grid_size / 2) * 1.5
                    z_coord = (v - grid_size / 2) * 1.5
                    
                    # Compute non-Euclidean state-wave matrix heights
                    # This simulates our eigenvalue deformations across time
                    y_height = math.sin(x_coord * 0.2 + t) * math.cos(z_coord * 0.2 + t) * 3.0
                    
                    mesh_data.append({
                        "x": x_coord,
                        "y": y_height,
                        "z": z_coord
                    })
            
            # Pack payload and broadcast over the data line
            payload = {
                "timestamp": t,
                "status": "EIGENFLOW_ACTIVE",
                "geometry": mesh_data
            }
            
            await websocket.send_text(json.dumps(payload))
            await asyncio.sleep(0.016)  # ~60 FPS broadcast speed
            t += 0.03
            
    except Exception as e:
        print(f"// CONNECTION SEVERED: {e} //")
    finally:
        try:
            await websocket.close()
        except:
            pass

if __name__ == "__main__":
    # Boot server locally on port 8000
    uvicorn.run("main:app", host="127.0.0.1", port=8000, reload=True)
