import express from 'express';
import cors from 'cors';

const app = express();

app.use(cors());

app.get('/', (req, res) => {
    res.json({
        date: new Date().toLocaleString('pt-BR'),
        status: 'API no Render funcionando!'
    });
});

// Porta dinâmica para o Render
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log('Servidor rodando na porta ${PORT}');
});