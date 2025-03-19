const express = require("express");
const cors = require("cors");
const { exec } = require("child_process");

const app = express();
app.use(cors());
app.use(express.json());

app.get("/api/dispositivos", (req, res) => {
    exec("./casa_inteligente", (error, stdout, stderr) => {
        if (error) {
            console.error("Erro ao executar o programa C:", error);
            return res.status(500).json({ erro: "Erro interno" });
        }
        try {
            // Se houver conteúdo extra, pode ser necessário fazer stdout.trim()
            const data = JSON.parse(stdout.trim());
            res.json(data);
        } catch (e) {
            console.error("Erro ao processar JSON:", e, stdout);
            res.status(500).json({ erro: "Resposta inválida do backend" });
        }
    });
});

app.listen(1337, () => console.log("🔥 Servidor rodando na porta 1337"));
