import React, { useState, useEffect } from "react";
import "./App.css";

export default function SmartHome() {
  const [devices, setDevices] = useState([]);
  const [newDevice, setNewDevice] = useState({
    descricao: "",
    tipo: "",
    status: "",
    sensores: "" // Campo para sensores, como uma string separada por vírgula
  })                          1 784221w3722222
  useEffect(() => {
    fetch("http://localhost:1337/api/dispositivos")
      .then((res) => res.json())
      .then((data) => {
        // Se o backend retornar a propriedade 'dispositivos'
        setDevices(data.dispositivos || []);
      })
      .catch((error) => {
        console.error("Erro ao buscar dispositivos:", error);
      });
  }, []);

  const handleChange = (e) => {
    setNewDevice({ ...newDevice, [e.target.name]: e.target.value });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    // Cria o corpo da requisição, incluindo o campo 'sensores'
    const formBody = `descricao=${encodeURIComponent(newDevice.descricao)}&tipo=${encodeURIComponent(newDevice.tipo)}&status=${encodeURIComponent(newDevice.status)}&sensores=${encodeURIComponent(newDevice.sensores)}`;

    fetch("http://localhost:1337/api/dispositivos", {
      method: "POST",
      headers: { "Content-Type": "application/x-www-form-urlencoded" },
      body: formBody
    })
      .then((res) => res.json())
      .then((data) => {
        alert(data.mensagem);
        // Supondo que o backend não retorne o objeto criado, atualizamos localmente:
        const sensorArray = newDevice.sensores.split(",").map((s) => s.trim());
        const newDeviceObj = {
          id: devices.length + 1,
          descricao: newDevice.descricao,
          tipo: newDevice.tipo,
          status: newDevice.status,
          sensores: sensorArray
        };
        setDevices([...devices, newDeviceObj]);
        setNewDevice({ descricao: "", tipo: "", status: "", sensores: "" });
      })
      .catch((error) => console.error("Erro ao adicionar dispositivo:", error));
  };

  return (
    <div className="container">
      <h1>🏠 Dispositivos Inteligentes</h1>

      <form onSubmit={handleSubmit}>
        <input
          type="text"
          name="descricao"
          placeholder="Descrição"
          value={newDevice.descricao}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="tipo"
          placeholder="Tipo"
          value={newDevice.tipo}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="status"
          placeholder="Status"
          value={newDevice.status}
          onChange={handleChange}
          required
        />
        <input
          type="text"
          name="sensores"
          placeholder="Sensores (ex: Luminosidade, Movimento)"
          value={newDevice.sensores}
          onChange={handleChange}
          required
        />
        <button type="submit">Adicionar Dispositivo</button>
      </form>

      <div className="device-list">
      {devices && devices.length > 0 ? (
          devices.map((device) => (
            <div key={device.id} className="device-card">
              <h2>{device.descricao}</h2>
              <p>
                <strong>Tipo:</strong> {device.tipo} | <strong>Status:</strong>{" "}
                {device.status}
              </p>
              {device.sensores && Array.isArray(device.sensores) && (
                <p>
                  <strong>Sensores:</strong> {device.sensores.join(", ")}
                </p>
              )}
            </div>
          ))
        ) : (
          <p>Nenhum dispositivo encontrado.</p>
        )}
      </div>
    </div>
  );
}
