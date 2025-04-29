import { useEffect, useState } from "react";
import "./App.css";

function App() {
  const [dateTime, setDateTime] = useState("");

  useEffect(() => {
    fetch("https://apiexpressdesenvolvimentoweb.onrender.com")
      .then((response) => response.json())
      .then((data) => setDateTime(data.date))
      .catch((error) => console.error("Erro ao buscar a data:", error));
  }, []);

  return (
    <div className="App">
      <h1>Data e Hora</h1>
      <p className="date-time">{dateTime ? dateTime : "Carregando..."}</p>
    </div>
  );
}

export default App;
